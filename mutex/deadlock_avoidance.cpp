#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::cout << "Thread A trying to lock mutexes 1 and 2..."<<std::endl;
    std::scoped_lock scoped_lck(mut1, mut2);
    std::cout << "Thread A has locked mutexes 1 and 2"<<std::endl;
    std::this_thread::sleep_for(50ms);
    std::cout<<"Thread A releasing mutexes 1 and 2..."<<std::endl;
}

void funcB()
{
    std::cout << "Thread B trying to lock mutexes 2 and 1..."<<std::endl;
    std::scoped_lock scoped_lck(mut2, mut1);
    std::cout<<"Thread B has locked mutexes 2 and 1"<<std::endl;
    std::this_thread::sleep_for(50ms);
    std::cout<<"Thread B releasing mutexes 2 and 1..."<<std::endl;
}

int main()
{
    std::thread thrA(funcA);
    std::thread thrB(funcB);

    thrA.join();
    thrB.join();
}
