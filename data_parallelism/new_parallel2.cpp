#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector<int> v{1,2,3,4};
    vector<int> v2;
    transform(v.begin(), v.end(), back_inserter(v2), [](int n){return 2*n;}
    );

    std::cout << "Input vector: ";
    for (auto i : v)
    {
        std::cout << i << ", ";
    }

    std::cout << "Output Vector: ";
    for (auto i : v2)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}