#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 100);

    int N = 10000; // Задайте нужное значение N

    // std::set
    std::set<int> mySet;
    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) {
        mySet.insert(dis(gen));
    }
    auto endTime = std::chrono::steady_clock::now();
    auto setInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    // std::vector
    std::vector<int> myVector;
    startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) {
        myVector.push_back(dis(gen));
    }
    std::sort(myVector.begin(), myVector.end());
    endTime = std::chrono::steady_clock::now();
    auto vectorSortTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    std::cout << "Время выполнения вставки в std::set: " << setInsertTime << " микросекунд" << std::endl;
    std::cout << "Время выполнения сортировки в std::vector: " << vectorSortTime << " микросекунд" << std::endl;

    if (setInsertTime < vectorSortTime) {
        std::cout << "std::set выполняется быстрее" << std::endl;
    } else if (vectorSortTime < setInsertTime) {
        std::cout << "std::vector выполняется быстрее" << std::endl;
    } else {
        std::cout << "Время выполнения одинаковое" << std::endl;
    }

    return 0;
}
