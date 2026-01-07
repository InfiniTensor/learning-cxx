#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 逻辑：从当前已经缓存的位置开始计算，直到达到索引 i
    // 注意：访问结构体成员需要使用 . 运算符
    for (; cache.cached <= i; ++cache.cached) {
        cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // 初始化 cache 数组的前两项为 {0, 1}，并将 cached 设为 2（表示已缓存两项）
    // 其余数组元素会自动初始化为 0
    FibonacciCache fib{{0, 1}, 2};

    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}