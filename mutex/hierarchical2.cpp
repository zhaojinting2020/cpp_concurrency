#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

using namespace std::literals;

constexpr int nforks = 5;
constexpr int nphilosophers = nforks;

std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

int mouthfuls[nphilosophers] = {0};

constexpr auto think_time = 2s;
constexpr auto eat_time = 1s;

constexpr auto time_out = think_time;

std::mutex fork_mutex[nforks];
std::mutex print_mutex;

void print(int n, const std::string& str, int lfork, int rfork)
{
    std::lock_guard<std::mutex> print_lock(print_mutex);
    std::cout << "Philosopher " << names[n] <<str;
    std::cout << lfork << " and " << rfork << std::endl;
}

void print(int n, const std::string& str, int forkno)
{
    std::lock_guard<std::mutex> print_lock(print_mutex);
    std::cout << "Philosopher " << names[n] << str << forkno << std::endl;
}

void print(int n, const std::string& str)
{
    std::lock_guard<std::mutex> print_lock(print_mutex);
    std::cout << "Philosopher " << names[n] << str << std::endl;
}

void dine(int phil_no)
{
    int lfork = phil_no;
    int rfork = (phil_no+1) % nforks;


    if (lfork > rfork)
    {
        std::swap(lfork, rfork);
    }

    print(phil_no, "'s forks are ", lfork, rfork);
    print(phil_no, " is thinking...");

    std::this_thread::sleep_for(think_time);
    print(phil_no, " reaches for fork number ", lfork);
    fork_mutex[lfork].lock();
    print(phil_no, " picks up fork ", lfork);
    print(phil_no, " is thinking...");

    std::this_thread::sleep_for(think_time);

    print(phil_no, " reaches for fork number ", rfork);
    fork_mutex[rfork].lock();

    print(phil_no, " is eating...");

    print(phil_no, " puts down fork ", lfork);
    print(phil_no, " puts down fork ", rfork);
    print(phil_no, " is thinking...");

    fork_mutex[lfork].unlock();
    fork_mutex[rfork].unlock();
    std::this_thread::sleep_for(think_time);
}

int main()
{
    std::vector<std::thread> philos;

    for(int i=0; i<nphilosophers; ++i)
    {
        philos.push_back(std::move(std::thread{dine, i}));
    }

    for(auto& philo : philos)
    {
        philo.join();
    }

    for(int i=0; i<nphilosophers; ++i)
    {
        std::cout << "Philosopher "<<names[i];
        std::cout << " had " << mouthfuls[i] << " mouthful" << std::endl;
    }

    return 0;
}