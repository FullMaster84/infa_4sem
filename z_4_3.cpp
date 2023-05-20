#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadsafePriorityQueue {
private:
    std::priority_queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;

public:
    ThreadsafePriorityQueue() {}

    void push(T value) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(value);
        lock.unlock();
        m_cv.notify_one();
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty()) {
            return false;
        }

        value = m_queue.top();
        m_queue.pop();
        return true;
    }

    void wait_pop(T& value) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return !m_queue.empty(); });

        value = m_queue.top();
        m_queue.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
};