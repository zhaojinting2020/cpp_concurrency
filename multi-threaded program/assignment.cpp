#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex counterMutex;
int counter = 0;

void task()
{
    for (int i = 0; i < 100000; ++i)
    {
        std::lock_guard<std::mutex> lock(counterMutex); // Lock the mutex
        counter++; // Increment the shared global variable safely
    }
}

int main()
{
    constexpr int numThreads = 1000; // Increase this number to see anomalous results

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(task);
    }

    for (std::thread& thr : threads)
    {
        thr.join();
    }

    std::cout << "Final value of counter: " << counter << std::endl;

    return 0;
}
