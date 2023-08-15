#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <string>
#include <future>

using namespace std;

class concurrent_queue_exception : public std::runtime_error
{
    public:
    concurrent_queue_exception() : std::runtime_error("Queue is empty") {}
    concurrent_queue_exception(const char* s) : std::runtime_error(s) {}
};

template <class T>
class concurrent_queue
{
    std::mutex m;
    std::queue<T> q;

public:
    concurrent_queue() = default;
    void push(T value)
    {
        std::lock_guard<std::mutex> lg(m);
        q.push(value);
    }

    void pop(T& value)
    {
        std::unique_lock<std::mutex> lg(m);
        if(q.empty())
        {
            throw concurrent_queue_exception("Queue is empty");
        }
        value = q.front();
        q.pop();
    }
};

concurrent_queue<string> cq;

void reader()
{
    string sdata;
    try
    {
        cout << "Reader calling pop ... " << endl;
        cq.pop(sdata);
        cout << "Reader received data: " << sdata << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr <<"Exception called: " << e.what() << '\n';
    }
}

void writer()
{
    std::this_thread::sleep_for(5s);
    cout << "Writer calling push ... " << endl;
    cq.push("Populated");
    cout << "Writer returned from push ... " << endl;
}

int main()
{
    auto w = async(std::launch::async, writer);
    std::this_thread::sleep_for(15s);
    auto r = async(std::launch::async, reader);
    r.wait();
    w.wait();
}