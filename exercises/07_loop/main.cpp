#include "../exercise.h"

// 缓存优化的斐波那契计算
static unsigned long long fibonacci(int i) {
    static unsigned long long cache[96] = {0, 1};  // 初始化前两个斐波那契数
    static int cached = 2;  // 已经计算的斐波那契数的个数

    // 如果已经计算过，则直接返回缓存的值
    if (i < cached) {
        return cache[i];
    }

    // 如果尚未计算，则通过迭代进行计算并缓存
    for (int j = cached; j <= i; ++j) {
        cache[j] = cache[j - 1] + cache[j - 2];
    }
    cached = i + 1;  // 更新缓存的最大索引
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
