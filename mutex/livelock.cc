#include <thread>
#include <iostream>

int x{0};

void func() {
    while (x == 0) {
        x = 1 - x;
        std::cout << "x=" << x <<std::endl;
    }
}

int main()
{
    std::thread thr1{ func };
    std::thread thr2{ func };
	
	thr1.join();
	thr2.join();
}

