#include <iostream>
#include <thread>
#include <future>

void calculate(std::promise<int>& p, int a, int b)
{
    int result { a + b };
    p.set_value(result);
}

void display(std::future<int>& f)
{
    std::cout << "Waiting for the result..." << std::endl;
    int result { f.get() };
    std::cout << "The result is " << result << std::endl;
}

int main()
{
    std::promise<int> p;
    std::future<int> f { p.get_future() };

    std::thread t1 {display, std::ref(f)};
    std::thread t2 {calculate, std::ref(p), 6, 7};

    t1.join();
    t2.join();
    return 0;
}