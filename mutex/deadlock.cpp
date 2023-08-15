#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::cout << "Thread A trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard1(mut1);
    std::cout << "Thread A has locked mutex 1\n";
    std::this_thread::sleep_for(50ms);


    std::cout << "Thread A trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard2(mut2);
    std::cout << "Thread A has locked mutex 2\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread A releases all its locks\n";
}

void funcB()
{
    std::cout << "Thread B trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard1(mut2);
    std::cout << "Thread B has locked mutex 2\n";
    std::this_thread::sleep_for(50ms);


    std::cout << "Thread B trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard2(mut1);
    std::cout << "Thread B has locked mutex 1\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread B releases all its locks\n";
}

int main()
{
    std::thread thrA(funcA);
    std::thread thrB(funcB);

    thrA.join();
    thrB.join();
}