#include <iostream>
#include <random>
#include <thread>
#include <atomic>

double estimatePiSequential(std::size_t numSamples) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    std::size_t numInsideCircle = 0;

    for (std::size_t i = 0; i < numSamples; ++i) {
        double x = dis(gen);
        double y = dis(gen);

        if (x * x + y * y <= 1.0)
            ++numInsideCircle;
    }

    return 4.0 * static_cast<double>(numInsideCircle) / static_cast<double>(numSamples);
}

void estimatePiParallel(std::size_t numSamples, std::atomic<std::size_t>& numInsideCircle) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    std::size_t numInside = 0;

    for (std::size_t i = 0; i < numSamples; ++i) {
        double x = dis(gen);
        double y = dis(gen);

        if (x * x + y * y <= 1.0)
            ++numInside;
    }

    numInsideCircle += numInside;
}

double estimatePiParallel(std::size_t numSamples, std::size_t numThreads) {
    std::atomic<std::size_t> numInsideCircle(0);
    std::size_t samplesPerThread = numSamples / numThreads;

    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(estimatePiParallel, samplesPerThread, std::ref(numInsideCircle));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 4.0 * static_cast<double>(numInsideCircle) / static_cast<double>(numSamples);
}

int main() {
    std::size_t numSamples = 10000000;
    std::size_t numThreads = std::thread::hardware_concurrency();

    double piSequential = estimatePiSequential(numSamples);
    double piParallel = estimatePiParallel(numSamples, numThreads);

    std::cout << "Estimated value of pi (sequential): " << piSequential << std::endl;
    std::cout << "Estimated value of pi (parallel): " << piParallel << std::endl;

    return 0;
}
