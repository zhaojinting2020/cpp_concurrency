#include <vector>
#include <string>
#include <chrono>
#include <mutex>
#include <iostream>
#include <thread>

using namespace std::literals;

constexpr int nforks = 5;
constexpr int nphilosophers = nforks;

std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

int mouthfuls[nphilosophers] = {0};
constexpr auto think_time = 2s;
constexpr auto eat_time = 1s;

std::mutex fork_mutex[nforks];
std::mutex print_mutex;


void print(int n, const std::string& str, int forkno)
{
    std::lock_guard<std::mutex> print_lock(print_mutex);
    std::cout << "Philosopher "<< names[n] << str <<forkno<<std::endl;
}

void print(int n, const std::string& str)
{
    std::lock_guard<std::mutex> print_lock(print_mutex);
    std::cout << "Philosopher " << names[n] << str << std::endl;
}

void dine(int nphilo)
{
    int lfork = nphilo;
    int rfork = (nphilo+1) % nforks;

    print(nphilo, " left fork is number ", lfork);
    print(nphilo, " right fork is number ", rfork);

    print(nphilo, " is thinking...");
    std::this_thread::sleep_for(think_time);

    print(nphilo, " reaches for fork number ", lfork);
    fork_mutex[lfork].lock();
    print(nphilo, " picks up fork ", lfork);

    print(nphilo, " is thinking...");
    std::this_thread::sleep_for(think_time);

    print(nphilo, " reaches for fork number ", rfork);
    fork_mutex[rfork].lock();
    print(nphilo, " picks up fork ", rfork);

    print(nphilo, " is eating...");
    std::this_thread::sleep_for(eat_time);

    print(nphilo, " puts down fork ", lfork);
    print(nphilo, " puts down fork ", rfork);
    print(nphilo, " is thinking...");

    fork_mutex[lfork].unlock();
    fork_mutex[rfork].unlock();
    std::this_thread::sleep_for(think_time);
}

int main()
{
    std::vector<std::thread> philos;

    for (int i=0; i<nphilosophers; ++i)
    {
        philos.push_back(std::move(std::thread(dine, i)));
    }

    for(auto& philo:philos)
    {
        philo.join();
    }

    for (int i=0; i<nphilosophers; ++i)
    {
        std::cout << "Philosopher " <<names[i];
        std::cout << " had " << mouthfuls[i] << " mouthfuls\n";
    }
}

