#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached; // 用于记录当前已经缓存的斐波那契数列的索引
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    /*
    for (; false; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    return cache.cache[i];
    */
    if (i <= cache.cached) {
        return cache.cache[i]; // 如果缓存中有结果，直接返回
    }
    // 如果缓存中没有结果，计算并存储
    for (int j = cache.cached + 1; j <= i; ++j) {
        cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
    }
    cache.cached = i; // 更新已缓存的最大索引
    return cache.cache[i]; // 返回第 i 个斐波那契数
    
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    // FibonacciCache fib;
    FibonacciCache fib{ {0, 1}, 1 }; // 为 fib 这个结构体变量进行初始化，给 cache 数组的前两个元素和 cached 成员赋值。
    /*
    { {0, 1}, 1 } 是初始化语法，它通过列表初始化方式给结构体中的成员赋初值。

    {0, 1} 初始化 cache 数组的前两个元素，也就是斐波那契数列的前两个数：0 和 1。

        cache[0] 被初始化为 0，表示斐波那契数列的第一个数。

        cache[1] 被初始化为 1，表示斐波那契数列的第二个数。

    1 初始化 cached，表示已经缓存的最大索引是 1。也就是说，cache[0] 和 cache[1] 已经存有值，缓存到了 cached 索引 1 位置。

    使用列表初始化可以确保 cache 数组和 cached 成员在声明时就被正确初始化，避免了可能的未定义行为或需要后续赋值。
    FibonacciCache 结构体通过这样的初始化，使得它能够高效地存储斐波那契数列的计算结果，同时跟踪已经缓存的斐波那契数列的索引，避免重复计算。
    */
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
