#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std::literals;

int task()
{
    std::cout << "executing task() in thread with ID:";
    std::cout << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Returning from task()" << std::endl;

    return 42;
}

void func(const std::string& option = "default")
{
    
}