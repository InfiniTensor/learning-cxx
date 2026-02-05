#include "../exercise.h"
#include <iostream>

/*
// Performance improved version: Reduce time complexity from O(2^n) to O(n)
constexpr unsigned long long fibonacci2(int n) {
    int i = 2;
    int f_1 = 1;
    int f_2 = 0;
    int f = 0;
    do {
        f = f_1 + f_2;
        f_2 = f_1;
        f_1 = f;
        i++;
    } while (i <= n);
    unsigned long long result = f;
    return result;
}
*/

constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;
    // std::cout << "fibonacci(20) = " << fibonacci(20) << std::endl;
    // std::cout << "fibonacci2(20) = " << fibonacci2(20) << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 10;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;
    // std::cout << "fibonacci2(90) = " << fibonacci2(90) << std::endl;

    return 0;
}
