#include <numeric>
#include <iostream>
#include <vector>
#include <execution>

using namespace std;
using namespace std::execution;

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8};
    
    auto sum = reduce(par_unseq, v.begin(), v.end(), 0);
    std::cout << "Vector elements: ";
    for (auto i : v)
    {
        std::cout << i << ", ";
    }
    std::cout << "Sum of elements is " << sum << std::endl;
}