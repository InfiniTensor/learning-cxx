#include "../exercise.h"
#include <utility>// 为使用 std::move

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        if (capacity > 0) cache[0] = 0;
        if (capacity > 1) cache[1] = 1;
    }

    // TODO: 实现移动构造器
    // 直接接管 other 的资源，并将 other 置于有效但未定义（通常为空）的状态
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached) {
        other.cache = nullptr;
        other.cached = 0;
    }

    // TODO: 实现移动赋值
    // ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            // 1. 释放现有资源
            delete[] cache;
            // 2. 窃取对方资源
            cache = other.cache;
            cached = other.cached;
            // 3. 将对方置空
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        if (cache) {
            delete[] cache;
        }
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i < cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 调用移动构造函数
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    // 调用移动赋值运算符
    fib0 = std::move(fib1);
    // 测试自赋值情况
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}