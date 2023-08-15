#include <iostream>
#include <string>
#include <thread>

using namespace std;

void func1(string&& str)
{
    cout << "Ownership of \"" << str << "\" transferred to thread" << "\n";
}

void func2(const string& str)
{
    cout << "Ownership of \"" << str << "\" transferred to thread" << "\n";
}


int main()
{
    string str1 = "moveable";
    string str2 = "reference";
    cout << "Starting thread" << '\n';

    thread thr1(func1, move(str1)); // thread function with rvalue arguments
    thr1.join();

    thread thr2(func2, cref(str2)); // thread function with reference/lvalue arguments
    thr2.join();

    cout << "Do I still have any data?\n" << ' ';
    cout << (str1.empty() ? "No" : "Yes") << ".\n";
    cout << (str2.empty() ? "No" : "Yes") << ".\n";

}