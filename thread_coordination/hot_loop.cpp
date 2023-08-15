#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::string sdata;

bool update_progress = false;
bool completed = false;

std::mutex data_mutex;
std::mutex completed_mutex;

void fetch_data()
{
    for (int i=0; i<5; ++i)
    {
        std::cout << "Fetcher thread waiting for data ... " << std::endl;
        std::this_thread::sleep_for(2s);

        std::lock_guard<std::mutex> data_lck(data_mutex);
        sdata += " Block " + std::to_string(i+1);
        std::cout << "sdata: " << sdata << std::endl;
        update_progress = true;
    }

    std::cout << "Fetch sdata has ended\n";
    std::lock_guard<std::mutex> completed_lck(completed_mutex);
    completed = true;
}

void progress_bar()
{
    size_t len=0;
    while (true)
    {
        std::cout << "Progress bar thread waiting for data ... " << std::endl;
        std::unique_lock<std::mutex> data_lck(data_mutex);
        while (!update_progress)
        {
            data_lck.unlock();
            std::this_thread::sleep_for(10ms);
            data_lck.lock();
        }
    

        len = sdata.size();

        update_progress = false;
        data_lck.unlock();

        std::cout << "Received " << len << " bytes so far " << std::endl;
        std::lock_guard<std::mutex> completed_lck(completed_mutex);
        if (completed)
        {
            std::cout << "Progress bar thread has ended" << std::endl;
            break;
        }
    }
}

void process_data()
{
    std::cout << "Processing thread waiting for data ..." << std::endl;

    std::unique_lock<std::mutex> completed_lck(completed_mutex);

    while(!completed)
    {
        completed_lck.unlock();
        std::this_thread::sleep_for(10ms);
        completed_lck.lock();
    }

    completed_lck.unlock();

    std::lock_guard<std::mutex> data_lck(data_mutex);
    std::cout << "Processing sdata: " << sdata << std::endl;
}

int main()
{
    std::thread fetcher(fetch_data);
    std::thread prog(progress_bar);
    std::thread processor(process_data);

    fetcher.join();
    prog.join();
    processor.join();
}