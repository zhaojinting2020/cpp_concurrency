#include <thread>
#include <iostream>

void hello()
{
    std::cout<<"Hello, Thread!\n";
}


// one try catch solution for thread management
// int main()
// {
//     std::thread thr(hello);
//     try
//     {
//         // it will cause end of the scope so thr will be terminated
//         thr.join();
//     }
//     catch(const std::exception& e)
//     {
//         std::cout<<"Exception caught: "<<e.what()<<"\n";
//         thr.join(); // thread still can execute
//     }
    
// }

// a more elegant solution for thread management

class thread_guard
{
    std::thread thr;

public:
    explicit thread_guard(std::thread&& thr) : thr(std::move(thr))
    {
    }

    ~thread_guard()
    {
        if(thr.joinable())
        {
            thr.join();
        }
    }

    // delete copy contructor and copy assignments
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
}

int main()
{
    try
    {
        std::thread thr(hello);
        thread_guard tguard{std::move(thr)};

        throw std::exception();
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception caught: "<<e.what() << "\n";
    }
    
    return 0;
}