#include <future>
#include <iostream>
#include <thread>

int produce()
{
    int x = 42;

    using namespace std::literals;

    std::this_thread::sleep_for(2s);

    if(0)
    {
        throw std::out_of_range("Oops");
    }

    std::cout << "Produce returning " << x << std::endl;
    return x;
}

int main()
{
    auto result = std::async(produce);
    try
    {
        int x = result.get();

        std::cout << "Get the return value x=" << x << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}
