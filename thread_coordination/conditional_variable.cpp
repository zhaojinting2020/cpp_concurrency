#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <condition_variable>

using namespace std::literals;

std::string sdata;
std::mutex mut;
std::condition_variable cond_var;

void reader()
{
    std::cout << "Reader thread locking mutex" << std::endl;
    std::unique_lock<std::mutex> uniq_lck(mut);
    std::cout << "Reader thread has locked the mutex" << std::endl;

    std::cout << "Reader thread sleeping" <<std::endl;
    cond_var.wait(uniq_lck);

    std::cout << "Reader thread wakes up" <<std::endl;
    std::cout << "Data is " << sdata << std::endl;
}

void writer()
{
    {
        std::cout << "Writer thread locking mutex" << std::endl;
        std::lock_guard<std::mutex> lck_guard(mut);
        std::cout << "Writer thread has locked the mutex" << std::endl;

        std::this_thread::sleep_for(2s);

        std::cout << "Writer thread modifying data ... " << std::endl;
        sdata = "Populated";
    }


    std::cout << "Writer thread send notification" <<std::endl;
    cond_var.notify_one();

}

int main()
{
    sdata = "Empty";
    std::cout << "Data is " << sdata << std::endl;

    std::thread read(reader);
    std::thread write(writer);

    write.join();
    read.join();
}