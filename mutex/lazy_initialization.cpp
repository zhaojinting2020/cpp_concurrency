#include <thread>
#include <iostream>
#include <mutex>

class Test{
public:
void func(){
    std::cout<<"Test"<<std::endl;
}
};

Test* ptest = nullptr;
std::mutex mut;

void process()
{
    std::unique_lock<std::mutex> uniq_lck(mut);

    if(!ptest)
    {
        std::lock_guard lck_guard(mut);

        if(!ptest)
        {
            ptest = new Test;
        }
    }
    ptest->func();
}