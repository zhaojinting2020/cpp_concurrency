#include <vector>
#include <list>
#include <thread>
#include <iostream>

template <typename T>
struct LockFreeQueue
{
    private:
        std::list<T> list;
        typename std::list<T>::iterator iHead, iTail;

    public:
    LockFreeQueue()
    {
        list.push_back(T()); // a dummy element
        iHead = list.begin();
        iTail = list.end();
    }
    bool Consume(T& t)
    {
        auto iFirst = iHead;
        ++iFirst;
        if (iFirst!=iTail)
        {
            iHead = iFirst;
            t = *iHead;
            return true;
        }
        return false;
    }
    void Produce(const T& t)
    {
        list.push_back(t);
        iTail = list.end();
        list.erase(list.begin(), iHead);
    }
    void Print()
    {
        auto head = iHead;
        ++head;

        for (auto el = head; el != iTail; ++el)
        {
            std::cout << *el << ", ";
        }
        std::cout << "\n";
    }
};

int main()
{
    LockFreeQueue<int> lfq;
    std::vector<std::thread> threads;
    int j = 1;

    for (int i=0; i<10; ++i)
    {
        std::thread produce(&LockFreeQueue<int>::Produce, &lfq, std::ref(i));
        threads.push_back(std::move(produce));
        std::thread consume(&LockFreeQueue<int>::Consume, &lfq, std::ref(j));
        threads.push_back(std::move(consume));
    }

    for (auto& thr: threads)
    {
        thr.join();
    }

    lfq.Print();
}