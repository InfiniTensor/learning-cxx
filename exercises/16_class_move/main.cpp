#include "../exercise.h"

// DynFibonacci 类定义
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 构造器：动态分配缓存空间
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached) {
        // 将原对象的缓存指针置为 nullptr，防止析构时双重释放内存
        other.cache = nullptr;
        other.cached = 0;
    }

    // 移动赋值操作符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 防止自我赋值
            // 释放原本的资源
            delete[] cache;

            // 转移资源
            cache = other.cache;
            cached = other.cached;

            // 将原对象的缓存指针置为 nullptr，防止析构时双重释放内存
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // 析构器：释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 缓存优化的斐波那契计算
    size_t operator[](int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // 常量版本的 get 方法：仅能读取缓存中的值
    size_t operator[](int i) const {
        // 如果缓存已经被移动（为空），返回错误或抛出异常
        ASSERT(cache != nullptr, "Accessing moved-from object.");
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
