#include "../exercise.h"

/// @brief 任意缓存容量的斐波那契类型。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 1. 使用 new size_t[capacity] 申请内存
    // 2. 初始化前两项并设置已缓存计数
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        if (capacity > 0) cache[0] = 0;
        if (capacity > 1) cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    // 必须使用 delete[] 而不是 delete，因为申请的是数组
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 逻辑：从当前位置计算到索引 i
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // 提醒：为了严谨，RAII 类通常需要禁用拷贝构造函数和赋值运算符，
    // 但在这个基础练习中可以先不写。
    DynFibonacci(DynFibonacci const &) = delete;
    DynFibonacci &operator=(DynFibonacci const &) = delete;
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}