#include "../exercise.h"
#include <iostream>

// 递归 constexpr 版本（只适合小 n，在编译期演示用）
constexpr unsigned long long fibonacci_constexpr(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci_constexpr(i - 1) + fibonacci_constexpr(i - 2);
    }
}

// 迭代版本，O(n)，适合运行时大 n
unsigned long long fibonacci_iter(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char **argv) {
    // 编译期计算小规模
    constexpr auto FIB20 = fibonacci_constexpr(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // 大规模用迭代计算（运行时）
    constexpr auto ANS_N = 90;
    auto ANS = fibonacci_iter(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
