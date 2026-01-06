#include "../exercise.h"

// 斐波那契数列缓存结构
struct FibonacciCache {
    unsigned long long cache[16];
    int cached;

    // 构造函数初始化缓存
    FibonacciCache() {
        cache[0] = 0;
        cache[1] = 1;
        cached = 2;
    }
};

// 缓存优化的斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 如果 i 小于已经缓存的数值，直接返回缓存中的值
    if (i < cache.cached) {
        return cache.cache[i];
    }

    // 从已缓存的地方开始计算
    for (int j = cache.cached; j <= i; ++j) {
        cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
    }

    // 更新缓存的已计算数目
    cache.cached = i + 1;

    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化缓存结构体
    FibonacciCache fib;
    
    // 计算并验证斐波那契数列的值
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;

    return 0;
}
