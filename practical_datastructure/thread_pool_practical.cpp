
#include <atomic>
#include <thread>
#include <functional>
#include <mutex>
#include <iostream>

using Func = std::function<void()>;
using namespace std;

template <class T>
class concurrent_queue_cv
{
    std::mutex m;
    std::queue<T> q;
    std::condition_variable cv;

    public:
    concurrent_queue_cv() = default;
    void push(T value)
    {
        std::lock_guard<std::mutex> lg(m);
        q.push(value);
        cv.notify_one();
    }

    void pop(T& value)
    {
        std::unique_lock<std::mutex> lg(m);
        cv.wait(lg, [this]{return !q.empty();});
        value = q.front();
        q.pop();
    }
};

class thread_pool
{
    concurrent_queue_cv<Func> work_queue;
    std::vector<std::thread> threads;
    void worker();

    public:
    thread_pool();
    ~thread_pool();
    void submit(Func f);
};

thread_pool::thread_pool()
{
    const unsigned thread_count = thread::hardware_concurrency();
    for(unsigned i=0; i<thread_count; ++i)
    {
        threads.push_back(thread{&thread_pool::worker, this});
    }
}


thread_pool::~thread_pool()
{
    for(auto& t: threads)
    {
        t.join();
    }
}

void thread_pool::worker()
{
    while(true)
    {
        Func task;
        work_queue.pop(task);
        task();
    }
}

void thread_pool::submit(Func f)
{
    work_queue.push(f);
}

mutex m;

void task()
{
    lock_guard<mutex> lg(m);
    cout << "Thread id: " << this_thread::get_id() << " started task" <<endl;
    this_thread::sleep_for(100ms);
    cout << "Thread id: " << this_thread::get_id() << " finished task" << endl;
}
