#include <thread>
#include <mutex>
#include <iostream>

class Test
{
public:
    Test()
    {
        std::cout<<"Test constructor called\n";
    }

    void func()
    {
        std::cout<<"Test function called"<<std::endl;
    }
};

Test* ptest = nullptr;
std::once_flag ptest_flag;

void process()
{
    std::call_once(ptest_flag, [](){
        ptest = new Test;
    });
    ptest->func();
}

int main()
{
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join();
    thr2.join();
}