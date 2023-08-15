#include <iostream>
#include <thread>
#include <atomic>
#include <mutex> // Add this line for <mutex> support

class Singleton {
private:
    Singleton() {}  // Private constructor to prevent direct instantiation

public:
    static Singleton* getInstance() {
       if (!instance.load(std::memory_order_relaxed)) {
            // If not, acquire a lock to perform the initialization
            std::lock_guard<std::mutex> lock(mutex);

            // Double-check inside the lock
            if (!instance.load(std::memory_order_relaxed)) {
                instance.store(new Singleton(), std::memory_order_relaxed);
            }
        }

        return instance.load(std::memory_order_relaxed);
    }

private:
    static std::atomic<Singleton*> instance;
    static std::mutex mutex;
};

std::atomic<Singleton*> Singleton::instance(nullptr);
std::mutex Singleton::mutex;

int main() {
    std::thread t1([] {
        Singleton* s = Singleton::getInstance();
        std::cout << "Thread 1: " << s << std::endl;
    });

    std::thread t2([] {
        Singleton* s = Singleton::getInstance();
        std::cout << "Thread 2: " << s << std::endl;
    });

    t1.join();
    t2.join();

    return 0;
}