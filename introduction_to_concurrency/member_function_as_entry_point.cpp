#include <iostream>
#include <thread>

using namespace std;

class greeter{
    public:
    void hello();
};

void greeter::hello(){
    std::cout<<"Hello, member function thread!\n"<<std::endl;
}


int main(){

    greeter greet;

    std::thread thr(&greeter::hello, & greet);

    thr.join();

    return 0;
}