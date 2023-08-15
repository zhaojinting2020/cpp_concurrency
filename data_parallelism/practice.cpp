#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <future>
#include <random>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

double accum(double *beg, double *end)
{
    return std::accumulate(beg, end, 0.0);
}

double add_parallel(std::vector<double>& vec)
{
    auto vec0 = &vec[0];
    auto vsize = vec.size();

    auto fut1 = std::async(std::launch::async, accum, vec0, vec0+vsize/4);
    auto fut2 = std::async(std::launch::async, accum, vec0+vsize/4, vec0+2*vsize/4);
    auto fut3 = std::async(std::launch::async, accum, vec0+2*vsize/4, vec0+3*vsize/4);
    auto fut4 = std::async(std::launch::async, accum, vec0+3*vsize/4, vec0+vsize);

    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int main()
{
    std::vector<double> vec(16);
    std::iota(vec.begin(), vec.end(), 1.0);

    std::vector<double> vrand(10'000);
    std::generate(vrand.begin(), vrand.end(), [&vrand]() {return dist(mt);});

    std::cout << "Sum of first 16 integers: " << add_parallel(vec) << std::endl;
    std::cout << "Sum of 10'000 random numbers: " << add_parallel(vrand) << std::endl;

    return 0;
}