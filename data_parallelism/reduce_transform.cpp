#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

std::vector<int> data_to_transform = {1, 2, 3, 4, 5};

int transform(int value)
{
    return value * 2;
}

void transformer_thread(std::vector<int>& transformed_data, int data)
{
    int transformed_value = transform(data);

    transformed_data.push_back(transformed_value);
}

int reduce(const std::vector<int>& transformed_data)
{
    return std::accumulate(transformed_data.begin(), transformed_data.end(), 0);
}

int main()
{
    std::vector<int> transformed_data;
    std::vector<std::thread> threads;

    for(const auto& data: data_to_transform)
    {
        threads.emplace_back(transformer_thread, std::ref(transformed_data), data);
    }

    for(auto& thread: threads)
    {
        thread.join();
    }

    int result = reduce(transformed_data); 
    // reduce cannot return until all the transform threads have finished
    // reduce has to read the output containers from the transform threads
    // reduce has to start up its own threads

    std::cout << "Result of reduction: " << result << std::endl;

    return 0;
}