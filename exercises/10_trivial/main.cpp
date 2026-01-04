#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 循环条件：若已缓存的长度 < i，继续预计算到第i项（确保cache[i]存在）
    // 从当前已缓存的下一项开始计算（cached初始为2，从索引2开始）
    for (; cache.cached <= i; ++cache.cached) {
        // 斐波那契规则：第n项 = 第n-1项 + 第n-2项
        cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化缓存结构体：
    // 1. cache[0] = 0, cache[1] = 1（斐波那契起始值），其余元素默认0
    // 2. cached = 2（标记已预计算到索引1，下一个待计算索引为2）
    FibonacciCache fib = {
        .cache = {0, 1},  // 聚合初始化：显式初始化前2项，剩余项默认0
        .cached = 2       // 已缓存的项数（索引0和1已初始化，故为2）
    };

    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}