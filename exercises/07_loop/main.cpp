#include "../exercise.h"
#include <stdexcept>
// 不是，因为状态cache 在改变
static unsigned long long fibonacci(int i) {
    static unsigned long long cache[96]{0, 1}, cached{2};
    if (i > 96) {
        throw std::out_of_range("fibonacci() index out of range (must be 0 <= i <= 95)");
    }
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
