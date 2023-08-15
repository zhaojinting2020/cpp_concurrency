#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <string>

using namespace std::literals;

std::string sdata;

bool update_progress = false;
bool completed = false;

std::mutex data_mutex;
std::mutex completed_mutex;

std::condition_variable data_cv;
std::condition_variable completed_cv;


void fetch_data()
{
    for(int i=0; i<5; ++i)
    {
        std::cout << "Fetcher thread waiting for data ... " << std::endl;
        std::this_thread::sleep_for(2s);

        std::unique_lock<std::mutex> uniq_lck(data_mutex);
        sdata += "Block" + std::to_string(i+1);
        std::cout << "Fetch sdata: " << sdata << std::endl;
        update_progress = true;
        uniq_lck.unlock();
        data_cv.notify_all();
    }

    std::cout << "Fetch sdata has ended" <<std::endl;

    std::lock_guard<std::mutex> lg(completed_mutex);
    completed = true;
    completed_cv.notify_all();
}

void progress_bar()
{
    size_t len = 0;

    while(true)
    {
        std::cout << "Progress bar thread waiting for data ... " << std::endl;

        std::unique_lock<std::mutex> data_lck(data_mutex);
        data_cv.wait(data_lck, []{return update_progress;});

        len = sdata.size();

        update_progress = false;
        data_lck.unlock();

        std::cout << "Received " << len << " bytes so far " << std::endl;

        std::unique_lock<std::mutex> compl_lck(completed_mutex);

        if(completed_cv.wait_for(compl_lck, 10ms, []{return completed;})){
            std::cout << "Progress bar thread has ended" << std::endl;
            break;
        }
    }
}

void process_data()
{
    std::this_thread::sleep_for(200ms);
    std::cout << "Processing thread waiting for data ... " << std::endl;

    std::unique_lock<std::mutex> compl_lck(completed_mutex);

    completed_cv.wait(compl_lck, []{return completed;});
    compl_lck.unlock();

    std::lock_guard<std::mutex> data_lck(data_mutex);
    std::cout << "Processing sdata: " << sdata <<std::endl;

    // Process the data
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