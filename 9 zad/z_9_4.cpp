#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <chrono>

int main() {
    std::vector<int> data(1000000); // Пример данных для обработки

    // Пример 1: std::transform
    {
        std::vector<int> result(data.size());

        auto startTime = std::chrono::high_resolution_clock::now();
        std::transform(std::execution::seq, data.begin(), data.end(), result.begin(), [](int value) {
            return value * 2; // Пример операции над элементом
        });
        auto endTime = std::chrono::high_resolution_clock::now();

        auto sequentialDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        startTime = std::chrono::high_resolution_clock::now();
        std::transform(std::execution::par, data.begin(), data.end(), result.begin(), [](int value) {
            return value * 2; // Пример операции над элементом
        });
        endTime = std::chrono::high_resolution_clock::now();

        auto parallelDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        std::cout << "std::transform sequential time: " << sequentialDuration << " microseconds\n";
        std::cout << "std::transform parallel time: " << parallelDuration << " microseconds\n";
    }

    // Пример 2: std::accumulate
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        int sequentialResult = std::accumulate(data.begin(), data.end(), 0);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto sequentialDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        startTime = std::chrono::high_resolution_clock::now();
        int parallelResult = std::reduce(std::execution::par, data.begin(), data.end(), 0);
        endTime = std::chrono::high_resolution_clock::now();

        auto parallelDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        std::cout << "std::accumulate sequential result: " << sequentialResult << '\n';
        std::cout << "std::accumulate sequential time: " << sequentialDuration << " microseconds\n";
        std::cout << "std::accumulate parallel result: " << parallelResult << '\n';
        std::cout << "std::accumulate parallel time: " << parallelDuration << " microseconds\n";
    }

    // Пример 3: std::sort
    {
        std::vector<int> dataCopy = data;

        auto startTime = std::chrono::high_resolution_clock::now();
        std::sort(dataCopy.begin(), dataCopy.end());
        auto endTime = std::chrono::high_resolution_clock::now();

        auto sequentialDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        dataCopy = data;

        startTime = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, dataCopy.begin(), dataCopy.end());
        endTime = std::chrono::high_resolution_clock::now();

        auto parallelDuration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        std::cout << "std::sort sequential time: " << sequentialDuration << " microseconds\n";
        std::cout << "std::sort parallel time: " << parallelDuration << " microseconds\n";
    }

    return 0;
}