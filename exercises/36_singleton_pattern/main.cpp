#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
// 懒汉式单例模式 Logger 类 
class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex_);
        std::cout << "[LOG] " << message << std::endl;
    }

private:
    Logger() = default;
    ~Logger() = default;
    
    std::mutex logMutex_;  // 保护输出操作
};

// ---- 不要修改以下代码 ----

void logTest(int id) {
    for (int i = 0; i < 3; ++i) {
        Logger::getInstance().log(
            "Thread " + std::to_string(id) + " - Message " + std::to_string(i)
        );
    }
}

int main() {
    std::vector<std::thread> threads;
    
    // 创建5个线程同时写日志
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(logTest, i);
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}