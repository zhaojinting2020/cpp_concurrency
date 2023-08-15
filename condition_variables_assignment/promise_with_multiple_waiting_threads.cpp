#include <future>
#include <iostream>
#include <thread>
#include <chrono>

void produce(std::promise<int>& px)
{
    try
    {
        px.set_value(x);
    }
    catch(...)
    {
        px.set_exception(std::current_exception());    
    }
    
    using namespace std::literals;

    int x = 42;
    std::this_thread::sleep_for(2s);

    std::cout << "Promise sets shared state to " << x << std::endl;

    px.set_value(x);
}

void consume(std::future<int>& fx)
{
    int x = fx.get();
}

std::promise<int> prom;
std::future<int> fut = prom.get_future();
std::thread thr_producer(produce, std::ref(prom));
std::thread thr_consumer(consume, std::ref(fut));

int main()
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread thr_producer(produce, std::ref(prom));
    std::thread thr_consumer(consume, std::ref(fut));

    thr.consumer.join();
    thr.producer.join();
}