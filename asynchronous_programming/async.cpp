#include <future>
#include <iostream>
#include <chrono>
#include <thread>

unsigned long long fibonacci(unsigned long long n)
{
    if (n <=1)
    {
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    std::cout << "Calling fibonacci(44)\n";
    auto result = std::async(fibonacci, 44);

    using namespace std::literals;
    while (result.wait_for(1s) != std::future_status::ready)
    {
        std::cout << "Waiting for the result...\n";
    }

    std::cout << result.get() << std::endl;

    return 0;
}