#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

using namespace std;
using namespace std::execution;

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> v2{v.size()};

    partial_sum(v.begin(), v.end(), v2.begin());

    std::cout << "Original vector elements: ";
    for (auto i : v)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}