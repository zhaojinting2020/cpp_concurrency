#include <mutex>
#include <thread>
#include <iostream>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);

    std::cout<<"Thread A trying to lock mutexes 1 and 2"<<std::endl;

    auto idx = std::try_lock(uniq_lk1, uniq_lk2);
    if (idx!=-1)
    {
        std::cout << "try_lock failed on mutex with index " << idx << std::endl;
    }
    else
    {
        std::cout << "Thread A has locked mutexes 1 and 2 "<<std::endl;
        std::this_thread::sleep_for(50ms);
        std::cout << "Thread A releasing mutexes 1 and 2"<<std::endl;
    }
}

int main()
{
    funcA();
}