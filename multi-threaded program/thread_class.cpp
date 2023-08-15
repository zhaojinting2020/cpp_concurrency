#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

void hello(){
    std::cout << "Hello Thread!\n";
}

std::thread func(){
    std::thread thr(hello);
    return thr;
}

int main(){
    std::thread thr = func();
    std::cout<<"received thread with id "<<thr.get_id()<<'\n';
    thr.join();
    return 0;
}