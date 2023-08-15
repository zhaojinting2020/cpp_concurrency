#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::cout << "Thread A trying to lock mutexes 1 and 2 ..."<<std::endl;
    std::lock(mut1, mut2);
    std::cout << "Thread A has locked mutexes 1 and 2"<<std::endl;

    std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);
    std::cout << "Thread A has adopted the locks" << std::endl;

    std::this_thread::sleep_for(50ms);
    std::cout << "Thread A releasing mutexees 1 and 2..." << std::endl;
}

void funcB()
{
    std::cout << "Thread B trying to lock mutexes 2 and 1..."<<std::endl;
    lock(mut1, mut2);
    std::cout << "Thread B has locked mutexes 2 and 1..." << std::endl;

    std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);
    std::cout << "Thread B has adopted the locks"<<std::endl;

    std::this_thread::sleep_for(50ms);
    std::cout<<"Thread B releasing mutexes 2 and 1..." << std::endl;
}

int main()
{
    std::thread thrA(funcA);
    std::thread thrB(funcB);

    thrA.join();
    thrB.join();

    return 0;
}