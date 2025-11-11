#include <iostream>
#include <string>
#include <map>
#include <functional>

#include <chrono>
#include <memory>
#include <thread>
#include <queue>
#include <mutex>

#include <condition_variable>


class Dispatcher
{
public:
    using Event = std::string;
    using Handler = std::function<void()>;

public:
    Dispatcher(): running_(true), worker_(&Dispatcher::run, this)
    {
    }

    ~Dispatcher() {
        running_ = false;
        cv_.notify_all();

        if (worker_.joinable()) {
            worker_.join();
        }
    }

public:
    void registerHandler(const Event& event, const Handler& handler) {
        std::lock_guard<std::mutex> lock(m_handlers_);
        handlers_[event] = handler;
    }

    void dispatch(const Event& event) {
        {
            std::lock_guard<std::mutex> lock(m_events_);
            events_.emplace(event);
        }

        cv_.notify_all();
    }

private:
    void run() {
        while(running_) {
            std::unique_lock<std::mutex> lock(m_events_);
            cv_.wait(lock, [this]() { return events_.empty() == false || running_ == false ;});

            while(events_.empty() == false) {
                const auto& event = events_.front();
                events_.pop();
                lock.unlock();

                auto handler = handlers_.find(event);
                if(handlers_.find(event) == handlers_.end()) {
	                // log
					lock.lock();
					continue;
				}
				
				handler->second();
				lock.lock();
            }
        }
    }

private:
    bool running_;

    std::mutex m_handlers_;
    std::map<Event, Handler> handlers_;

    std::mutex m_events_;
    std::queue<Event> events_;

    std::thread worker_;

    std::condition_variable cv_;

};


int main() {
    Dispatcher dispatcher;

    std::cout << "Current thread id = " << std::this_thread::get_id() << std::endl;

    dispatcher.registerHandler("hello", []() { std::cout << "Hello from dispatcher! Thread id = " << std::this_thread::get_id() << std::endl; });
    dispatcher.registerHandler("language", []() { std::cout << "C++! Thread id = " << std::this_thread::get_id() << std::endl; });

    dispatcher.dispatch("language");
    dispatcher.dispatch("error");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    dispatcher.dispatch("hello");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return 1;
}