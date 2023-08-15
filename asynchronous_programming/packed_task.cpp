


std::packaged_task<int(int, int)> ptask([] (int a, int b)
{
    return a+b;
})

std::future<int> fut = ptask.get_future();

ptask(6, 7);

fut.get();