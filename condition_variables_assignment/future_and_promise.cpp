#include <future>
#include <iostream>
#include <thread>
#include <chrono>

void produce(std::promise<int>& px)
{
    using namespace std::literals;

    int x = 42;
    std::this_thread::sleep_for(2s);

    std::cout << "Promise sets shared state to " << x << "\n";

    px.set_value(x);
}

void consume(std::future<int>& fx)
{
    std::cout << "Future calling get() ... ";
    int x = fx.get();
    std::cout << "Future returns from calling get()" << std::endl;
    std::cout << "Ths answer is " << x << std::endl;
}

int main()
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread thr_producer(produce, std::ref(prom));
    std::thread thr_consumer(consume, std::ref(fut));

    thr_consumer.join();
    thr_producer.join();
}