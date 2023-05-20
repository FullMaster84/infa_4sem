#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template<typename Iterator, typename Function>
void parallel_for_each(Iterator begin, Iterator end, Function fn, std::size_t threshold) {
    std::size_t size = std::distance(begin, end);

    if (size <= threshold) {
        std::for_each(begin, end, fn);
    } else {
        Iterator mid = begin + size / 2;

        std::future<void> left = std::async(std::launch::async,
            [&]() { parallel_for_each(begin, mid, fn, threshold); });

        parallel_for_each(mid, end, fn, threshold);

        left.get();
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Параллельное применение функции к каждому элементу
    parallel_for_each(numbers.begin(), numbers.end(),
        [](int& num) { num *= 2; }, 2);

    // Вывод измененных элементов
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
