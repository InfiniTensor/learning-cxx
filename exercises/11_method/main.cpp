#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数初始化缓存
    
    Fibonacci() : cached(1){ // 初始化已缓存的索引为 1，表示已计算cache[0] 和 cache[1]
        // 初始化前两个斐波那契数
        cache[0] = 0; // 第一个斐波那契数
        cache[1] = 1; // 第二个斐波那契数
    }
    
    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        /*
        for (; false; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        */
        // 打印cached
        std::cout << "cached: " << cached << std::endl;  

        if (i <= cached) {
            return cache[i]; // 如果i已经计算过，直接返回缓存的值
        }
        // 计算并缓存数列的第i个数
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2]; // 计算斐波那契数并存储在缓存中
        }
        cached = i; // 更新已缓存的最大索引
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确，见上
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
