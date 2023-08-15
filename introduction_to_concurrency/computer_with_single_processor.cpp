#include <thread>
#include <iostream>

void hello(){
    std::cout<<"Hello, Thread!"<<std::endl;
}

int main(){
    std::thread thr(hello);
    std::cout << "Hello thread has native handle "<<thr.native_handle()<<"\n";
    thr.join();
    std::cout << "Hello thread has native handle "<<thr.native_handle()<<"\n";
    return 0;
}