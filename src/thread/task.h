#include <chrono>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
template <typename T>
class Safe_queue
{
    mutable std::mutex m;
    std::queue<T> data_queue;
    static const int MAX_CAPACITY = 100;

public:
    Safe_queue() = default;
    Safe_queue(const Safe_queue &other)
    {
        std::lock_guard<std::mutex> lk(m);
        data_queue = other.data_queue;
    }
    Safe_queue &operator=(const Safe_queue &other)
    {
        std::lock_guard<std::mutex> lk(m);
        data_queue = other.data_queue;
    }
    Safe_queue(Safe_queue &&other)
    {
        std::lock_guard<std::mutex> lk(m);
        data_queue = std::move(other.data_queue);
    }
    Safe_queue &operator=(Safe_queue &&other)
    {
        std::lock_guard<std::mutex> lk(m);
        data_queue = std::move(other.data_queue);
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lk(m);
        return data_queue.size();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lk(m);
        return data_queue.empty();
    }

    int push(const T &elem)
    {
        std::lock_guard<std::mutex> lk(m);
        if (data_queue.size() >= MAX_CAPACITY)
        {
            return -1;
        }
        data_queue.push(elem);
        return 0;
    }

    std::unique_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lk(m);
        if (data_queue.empty())
        {
            return nullptr;
        }
        std::unique_ptr<T> retVal(new T(data_queue.front()));
        data_queue.pop();
        return retVal;
    }
};
template <typename T>
class My_thread : public std::thread
{
    Safe_queue<T> cmdQueue;
    static const ONE_DEAL_NUM = 4;

public:
    // 继承 get_id, joinable、join和detach等
    virtual int handle_cmd(std::unique_ptr<T> cmd);
    void svc()
    {
        while (true)
        {
            if (cmdQueue.empty())
            {
                std::this_thread::sleep_for(std::chrono::duration<std::chrono::milliseconds> 100);
                continue;
            }
            for (size_t i = 0; i < ONE_DEAL_NUM; i++)
            {
                auto cmd = cmdQueue.pop();
                if (!cmd)
                {
                    break;
                }
                handle_cmd(cmd);
            }
            std::this_thread::yield();
        }
    }
    int notify(const T &cmd)
    {
        return cmdQueue.push(cmd);
    }
};