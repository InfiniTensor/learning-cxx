#include "../exercise.h"

// 改正函数实现，实现正确的缓存优化斐波那契计算
// 这个函数不是纯函数，因为它使用了static变量（缓存），其结果依赖于内部状态
static unsigned long long fibonacci(int i) {
    // 为缓存设置正确的初始值，fib[0]=0, fib[1]=1
    static unsigned long long cache[96] = {0, 1};
    static bool initialized = false;
    
    // 只初始化一次，预计算所有需要的斐波那契值
    if (!initialized) {
        for (int j = 2; j < 96; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        initialized = true;
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
