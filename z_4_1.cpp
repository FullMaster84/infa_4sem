#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mutex; // Мьютекс для безопасной работы с общим счетчиком
int points_in_circle = 0; // Общий счетчик точек, попавших в круг

// Функция, выполняемая каждым потоком
void monte_carlo_pi(int iterations)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    int points_inside = 0; // Счетчик точек, попавших в круг

    for (int i = 0; i < iterations; i++)
    {
        double x = dis(gen);
        double y = dis(gen);
        double distance = x * x + y * y;

        if (distance <= 1)
        {
            points_inside++;
        }
    }

    // Безопасно обновляем общий счетчик с помощью мьютекса
    std::lock_guard<std::mutex> lock(mutex);
    points_in_circle += points_inside;
}

int main()
{
    int num_threads = 4; // Количество потоков
    int iterations_per_thread = 1000000; // Количество итераций на каждом потоке

    std::vector<std::thread> threads;

    // Создаем и запускаем потоки
    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back(monte_carlo_pi, iterations_per_thread);
    }

    // Дожидаемся завершения работы всех потоков
    for (auto &thread : threads)
    {
        thread.join();
    }

    // Вычисляем оценку числа пи
    double pi_estimate = 4.0 * points_in_circle / (num_threads * iterations_per_thread);

    // Выводим результат
    std::cout << "Estimated value of pi: " << pi_estimate << std::endl;

    return 0;
}