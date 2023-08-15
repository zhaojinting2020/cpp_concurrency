#include <vector>
#include <iostream>
#include <execution>
#include <algorithm>

namespace se = std::execution;

int main()
{
    std::vector<int> vec{3, 1, 4, 1, 5, 9};

    std::sort(se::par, vec.begin(), vec.end(),
              [](int a, int b){
                return b<a;
              });

    for (auto i : vec)
    {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}
