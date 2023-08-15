#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>


using namespace std::chrono;

std::string sdata;
std::mutex mut;

std::condition_variable cond_var;

void reader()
{
    std::cout << "Reader thread locking mutex" << std::endl;
    std::unique_lock<std::mutex> uniq_lck(mut);
    std::cout << "Reader thread has locked the mutex" << std::endl;

    std::cout << "Reader thread sleeping ... " << std::endl;
    cond_var.wait(uniq_lck);

    std::cout << "Reader thread wakes up" << std::endl;
}

void writer()
{
    {
        std::cout << "Writer thread locking mutex" <<std::endl;

        std::lock_guard<std::mutex> lck_guard(mut);
        std::cout << "Writer thread has locked the mutex" <<std::endl;

        std::this_thread::sleep_for(2s);
    }
}