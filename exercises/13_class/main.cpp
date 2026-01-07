#include "../exercise.h"

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // TODO: 实现构造器
    // 使用初始化列表将 cache 的前两项设为 0, 1，并设置 cached 计数
    // 注意：数组在初始化列表中通常只能通过 {} 整体初始化或在函数体内赋值
    Fibonacci() : cache{0, 1}, cached(2) {
        // 构造函数体目前可以留空
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 逻辑同之前的练习：如果请求的项还没缓存，则循环计算
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在 Fibonacci 类拥有了无参构造器
    // 当声明 fib 时，它会自动调用 Fibonacci()，将 cached 设为 2，cache 前两项设为 0, 1
    Fibonacci fib;

    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}