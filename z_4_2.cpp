#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

std::mutex mutex; // Мьютекс для безопасной работы с результатами
std::vector<int> results;

// Функция, выполняемая каждым потоком
void search_fragment(const std::string& sequence, const std::string& fragment, int start, int end)
{
    // Ищем вхождения фрагмента в заданном диапазоне позиций
    for (int i = start; i < end; i++)
    {
        if (sequence.substr(i, fragment.size()) == fragment)
        {
            // Безопасно добавляем индекс позиции в результаты с помощью мьютекса
            std::lock_guard<std::mutex> lock(mutex);
            results.push_back(i);
        }
    }
}

int main()
{
    std::string sequence = "AGTTCAGTACGACTGACGATCAGTAGCGATCGATCGATCGATCGACTGACGACTGACTGACGATC"; // Пример нуклеотидной последовательности

    std::string fragment;
    std::cout << "Введите фрагмент для поиска: ";
    std::cin >> fragment;

    int num_threads = std::thread::hardware_concurrency(); // Количество доступных потоков
    int chunk_size = sequence.size() / num_threads;

    std::vector<std::thread> threads;

    // Создаем и запускаем потоки
    for (int i = 0; i < num_threads; i++)
    {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? sequence.size() : (i + 1) * chunk_size;
        threads.emplace_back(search_fragment, std::ref(sequence), std::ref(fragment), start, end);
    }

    // Дожидаемся завершения работы всех потоков
    for (auto& thread : threads)
    {
        thread.join();
    }

    // Выводим результаты
    if (results.empty())
    {
        std::cout << "Фрагмент не найден" << std::endl;
    }
    else
    {
        std::cout << "Найдены следующие вхождения фрагмента:" << std::endl;
        for (int i = 0; i < results.size(); i++)
        {
            std::cout << results[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
