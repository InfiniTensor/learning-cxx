#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数初始化缓存
    Fibonacci() {
        cache[0] = 0;
        cache[1] = 1;
        cached = 2; // 只缓存了 0 和 1
    }

    // 获取斐波那契数，并使用缓存优化
    unsigned long long get(int i) {
        if (i < cached) {
            return cache[i]; // 如果已缓存，直接返回
        }

        // 从已缓存的地方开始计算
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2]; // 计算并缓存
        }

        cached = i + 1; // 更新缓存已计算的个数
        return cache[i]; // 返回计算结果
    }
};

int main(int argc, char **argv) {
    // 初始化 Fibonacci 对象
    Fibonacci fib;

    // 计算斐波那契数并验证结果
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    return 0;
}
