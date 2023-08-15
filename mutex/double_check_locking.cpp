#include <thread>
#include <iostream>
#include <mutex>


class Test
{
    public:
    Test()
    {
        std::cout << "Test constructor called\n";
    }

    void func()
    {

    }
};

void process()
{
    static Test ptest;
    ptest.func();
}

int main()
{
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join();
    thr2.join();
}