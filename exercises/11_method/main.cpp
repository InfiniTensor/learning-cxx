#include "../exercise.h"
#include <iostream>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 如果请求的索引超出了当前缓存的范围，扩展缓存
        if (i >= cached) {
            // 确保至少有两个基础值来计算
            if (cached < 2) {
                // 如果缓存为空，初始化前两个值
                if (cached == 0) {
                    cache[0] = 0;// F(0)
                    cached = 1;
                }
                if (cached == 1) {
                    cache[1] = 1;// F(1)
                    cached = 2;
                }
            }

            // 计算并缓存从当前缓存位置到i的斐波那契数
            for (int j = cached; j <= i; ++j) {
                cache[j] = cache[j - 1] + cache[j - 2];
                ++cached;
            }
        }

        // 返回缓存中的值
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // 使用聚合初始化：第一个花括号初始化cache数组，第二个值初始化cached
    Fibonacci fib = {{0, 1}, 2};// 直接初始化前两个值和cached计数器

    // 或者使用值初始化，然后在get函数中动态计算
    // Fibonacci fib = {};  // 所有成员初始化为0，get函数会处理初始化

    // 验证斐波那契数列
    std::cout << "F(0) = " << fib.get(0) << std::endl;  // 0
    std::cout << "F(1) = " << fib.get(1) << std::endl;  // 1
    std::cout << "F(2) = " << fib.get(2) << std::endl;  // 1
    std::cout << "F(3) = " << fib.get(3) << std::endl;  // 2
    std::cout << "F(4) = " << fib.get(4) << std::endl;  // 3
    std::cout << "F(5) = " << fib.get(5) << std::endl;  // 5
    std::cout << "F(6) = " << fib.get(6) << std::endl;  // 8
    std::cout << "F(7) = " << fib.get(7) << std::endl;  // 13
    std::cout << "F(8) = " << fib.get(8) << std::endl;  // 21
    std::cout << "F(9) = " << fib.get(9) << std::endl;  // 34
    std::cout << "F(10) = " << fib.get(10) << std::endl;// 55

    // 测试断言
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    // 测试缓存效果：多次获取应该从缓存直接返回
    std::cout << "\nTesting cache performance:" << std::endl;
    std::cout << "F(15) = " << fib.get(15) << std::endl;// 610
    std::cout << "F(20) = " << fib.get(20) << std::endl;// 6765
    std::cout << "F(10) = " << fib.get(10) << std::endl;// 55 - 应该从缓存直接返回

    return 0;
}