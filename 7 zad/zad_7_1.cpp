#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

bool isPrime(int number) {
    if (number <= 1)
        return false;

    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0)
            return false;
    }

    return true;
}

int main() {
    // Создание последовательности П1 целых чисел от 1 до 10
    std::vector<int> P1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Добавление чисел в конец П1 из cin
    int num;
    std::cout << "Введите числа для добавления в П1 (Ctrl+D для завершения ввода): ";
    while (std::cin >> num) {
        P1.push_back(num);
    }

    // Перемешивание П1 случайным образом
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(P1.begin(), P1.end(), g);

    // Удаление дубликатов из П1
    std::sort(P1.begin(), P1.end());
    P1.erase(std::unique(P1.begin(), P1.end()), P1.end());

    // Подсчет количества нечетных чисел в П1
    int oddCount = std::count_if(P1.begin(), P1.end(), [](int num) { return num % 2 != 0; });

    // Определение минимального и максимального значений в П1
    int minVal = *std::min_element(P1.begin(), P1.end());
    int maxVal = *std::max_element(P1.begin(), P1.end());

    // Попытка найти хотя бы одно простое число в П1
    bool foundPrime = false;
    for (int num : P1) {
        if (isPrime(num)) {
            foundPrime = true;
            break;
        }
    }

    // Замена всех чисел в П1 их квадратами
    std::transform(P1.begin(), P1.end(), P1.begin(), [](int num) { return num * num; });

    // Создание последовательности П2 из N случайных чисел, где N - длина П1
    std::vector<int> P2(P1.size());
    std::random_device rd2;
    std::mt19937 g2(rd2());
    std::uniform_int_distribution<int> distribution(1, 100);
    std::generate(P2.begin(), P2.end(), [&distribution, &g2]() { return distribution(g2); });


    //int sumP2 = std::accumulate(P2.begin(), P2.end(), 0);

    // Вывод результатов
    std::cout << "П1: ";
    for (int num : P1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Количество нечетных чисел в П1: " << oddCount << std::endl;
    std::cout << "Минимальное значение в П1: " << minVal << std::endl;
    std::cout << "Максимальное значение в П1: " << maxVal << std::endl;
    std::cout << "Найдено ли простое число в П1: " << (foundPrime ? "Да" : "Нет") << std::endl;
    //std::cout << "Сумма чисел в П2: " << sumP2 << std::endl;

    return 0;
}
