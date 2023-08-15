#include <iostream>
#include <thread>
#include <string>
#include <atomic>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
atomic<bool> dataReady{false};
string sdata{"Empty"};

// Waiting thread
void reader() {
    unique_lock<std::mutex> guard(mut);  // Acquire lock
    while (!dataReady.load()) {
        guard.unlock();
        this_thread::yield();  // Release the lock and yield to avoid busy waiting
        guard.lock();           // Reacquire the lock
    }
    cout << "Data is " << sdata << endl;  // Use the new value
}

// Modifying thread
void writer() {
    cout << "Writing data..." << endl;
    {
        lock_guard<std::mutex> lg(mut);  // Acquire lock
        this_thread::sleep_for(2s);       // Pretend to be busy...
        sdata = "Populated";               // Modify the data
        dataReady.store(true);            // Set the flag to indicate data is ready
    }
}

int main() {
    cout << "Data is " << sdata << endl;
    thread read{reader};
    thread write{writer};

    write.join();
    read.join();
}
