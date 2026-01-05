#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    Fibonacci() : cached(0) {
        cache[0] = 0;  // F(0) = 0
        cache[1] = 1;  // F(1) = 1
        cached = 2;    // 已经缓存了前两个值
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        if (i < cached) {
            return cache[i];
        }
        
        // 计算并缓存从cached到i的所有值
        for (int n = cached; n <= i; ++n) {
            cache[n] = cache[n - 1] + cache[n - 2];
        }
        
        // 更新缓存的位置（i+1，因为数组从0开始）
        cached = i + 1;
        
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
