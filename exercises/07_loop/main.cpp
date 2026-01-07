#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(int i) {
    // 使用静态变量，cached 记录当前已经缓存到的最大索引
    // 初始化前两项：cache[0]=0, cache[1]=1，已经缓存到索引 1
    static unsigned long long cache[96]{0, 1}, cached = 2;

    // 如果请求的 i 已经超出了当前缓存的范围，则继续计算
    // 循环条件：只要 cached 还没达到或超过需要的 i + 1（即还没算出第 i 项），就继续
    for (; cached <= i; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }

    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}