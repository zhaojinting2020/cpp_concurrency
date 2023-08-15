#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

int counter = 0;
std::mutex mut;

void task()
{
    for(int i=0; i<100'000; ++i)
    {
        std::lock_guard<std::mutex> lck_guard(mut);
        ++counter;
    }
}

int main()
{
    std::vector<std::thread> tasks;
    for (int i=0; i<10; ++i)
    {
        tasks.push_back(std::thread(task));
    }

    for(auto& thr: tasks)
    {
        thr.join();
    }

    std::cout << counter << "\n";
}