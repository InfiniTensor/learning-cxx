#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
         if (i < 0 || i >= 128) {
           return false;
        }

        // 2. 缓存命中：目标值已计算，直接返回
        if (i < cached) {
            return cache[i];
        }

        // 3. 缓存未命中：从当前已缓存位置计算到目标i
        for (; cached <=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        // 更新已缓存的数量
        cached = i + 1;

        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib;
    fib.cache[0]=0;
    fib.cache[1]=1;
    fib.cached = 2;  
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
