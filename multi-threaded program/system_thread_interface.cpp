#include <thread>
#include <iostream>
#include <chrono>

using namespace std::literals;

void hello(){
    std::cout<<"Hello, Thread!"<<std::endl;
}

int main(){
    std::thread thr(hello);
    std::cout << "Hello thread has native handle "<<thr.native_handle()<<"\n";
    auto current_thread_id = std::this_thread::get_id();
    auto thr_id = thr.get_id();
    std::cout<<"current thread id="<<current_thread_id<<" thr_id="<<thr_id<<std::endl;

    

    thr.join();

    std::this_thread::sleep_for(std::chrono::seconds(2));


    std::cout << "\nHello thread has native handle "<<thr.native_handle()<<"\n";
    return 0;
}