#include "../exercise.h"
#include <iostream>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        ASSERT(i >= 0 && i < 128, "i out of range for 128-entry cache");

        // Guard: initialize F(0), F(1) and minimum index:
        if (cached < 2 || cached >= 128) cached = 2;
        if (cache[0] != 0) cache[0] = 0ULL;
        if (cache[1] != 1) cache[1] = 1ULL;

        // calculate Fibonacci
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib{{0, 1}, 2};
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
