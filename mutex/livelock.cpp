#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex mut1, mut2;

void funcA()
{
    bool locked = false;

    while(!locked)
    {
        std::lock_guard<std::mutex> lck_guard(mut1);
        std::cout << "After you, Cecil!" << std::endl;
        std::this_thread::sleep_for(1s);
        locked = mut2.try_lock();
    }
}

void funcB()
{
    bool locked = false;

    while(!locked)
    {
        std::lock_guard<std::mutex> lck_guard(mut2);
        std::cout << "After you, Claudie!" << std::endl;
        std::this_thread::sleep_for(1s);
        locked = mut1.try_lock();
    }   
}


int main()
{
    std::thread thrA(funcA);
    std::this_thread::sleep_for(10ms);
    std::thread thrB(funcB);

    thrA.join();
    thrB.join();
}
