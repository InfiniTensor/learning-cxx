#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 实现缓存优化的斐波那契计算：按需预计算，避免重复计算
    unsigned long long get(int i) {
        // 循环条件：若已缓存项数 < 目标索引i，继续计算到第i项
        // 从当前已缓存的下一项（cached）开始，直到覆盖目标i
        for (; cached <= i; ++cached) {
            // 斐波那契核心规则：第n项 = 第n-1项 + 第n-2项
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        // 此时cache[i]已预计算完成，直接返回
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化结构体：显式设置斐波那契起始值和已缓存项数
    // 避免读取未初始化变量（未定义行为）
    Fibonacci fib = {
        .cache = {0, 1},  // 聚合初始化：cache[0]=0（第0项）、cache[1]=1（第1项），剩余元素默认0
        .cached = 2       // 已缓存项数：索引0和1已初始化，下一个待计算索引为2
    };

    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}