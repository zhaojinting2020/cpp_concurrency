#include <iostream>
#include <string>
#include <algorithm>
#include <execution>

namespace se = std::execution;

int main()
{
    std::string str ("Hello World");
    std::cout << "String to serach: " << str << std::endl;

    std::cout << "Searching for first occurence of o" << std::endl;
    auto res = std::find(se::seq, str.cbegin(), str.cend(), 'o');

    if(res != str.end())
    {
        std::cout << "Found a matching element at index: " << res - str.cbegin() << std::endl;

        std::cout << "At this point in the string: ";
        for (auto it = res; it!= str.end(); ++it)
        {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No matching element" << std::endl;
    }

}