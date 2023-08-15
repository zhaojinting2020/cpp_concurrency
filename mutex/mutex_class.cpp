/*
std::mutex interface

lock()
try_lock()
unlock()

*/


#include <mutex>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

std::mutex the_mutex;

void task1()
{
    std::cout << "Task1 trying to lock the mutex" << std::endl;
    the_mutex.lock();
    std::cout << "Task1 has locked the mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task1 unlocking the mutex" << std::endl;
    the_mutex.unlock();
}

void task2()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task2 trying to lock the mutex" << std::endl;
    while(!the_mutex.try_lock())
    {
        std::cout << "Task2 could not lock the mutex" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Task2 has locked the mutex" <<std::endl;
    the_mutex.unlock();
}

int main()
{

    // while (!the_mutex.try_lock())
    // {
    //     std::cout<<"thread sleeps for 2 second"<<std::endl;
    //     std::this_thread::sleep_for(std::chrono::seconds(2));
    // }

    std::thread thr1(task1);
    std::thread thr2(task2);

    thr1.join();
    thr2.join();
}