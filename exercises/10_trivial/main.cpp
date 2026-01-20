#include "../exercise.h"
#include <iostream>

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &fc, int i) {
    ASSERT(i >= 0 && i < 16, "i out of range for 16-entry cache")
    // Guard: initialize F(0)=0, F(1)=1, and cached
    std::cout << fc.cached << std::endl;
    ASSERT(fc.cached >= 0 && fc.cached < 16, "fc.cached is out of range for 16 entry cache")
    if (fc.cached < 2) fc.cached = 2;
    if (fc.cache[0] != 0) fc.cache[0] = 0ULL;
    if (fc.cache[1] != 1) fc.cache[1] = 1ULL;
    // Fill in the Fibonacci variables
    for (; fc.cached <= i; ++fc.cached) {
        fc.cache[fc.cached] = fc.cache[fc.cached - 1] + fc.cache[fc.cached - 2];
    }
    return fc.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib{{0ULL, 1ULL}, 2};
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
