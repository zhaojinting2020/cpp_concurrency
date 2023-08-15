#include <iostream>
#include <thread>

using namespace std;

int main(){
    int i=3;
    std::thread thr([&i]()-> void{i*= 2;});

    thr.join();

    std::cout<< "The value of i is "<<i<<std::endl;

    std::thread thr2(
        [](int i1, int i2){
            std::cout << "The sum of "<<i1<<" and "<<i2<<" is "<<i1+i2<<"\n";
            }, 
        2, 3);

    thr2.join();

    return 0;
}