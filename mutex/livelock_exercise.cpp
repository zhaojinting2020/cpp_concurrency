#include <iostream>
#include <thread>
#include <mutex>

int x{0};
std::mutex x_mutex;

void func() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(x_mutex);
            if (x == 0) {
                x = 1;
                break;
            }
        }
    }
}

int main() {
    std::thread thr1{ func };
    std::thread thr2{ func };
    
    thr1.join();
    thr2.join();
}
