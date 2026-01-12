#include "../exercise.h"

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

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 20; // 值太大，编译时运算会超出编译器限制 进行的操作次数超过了编译器默认的限制（33554432次操作）。这意味着这个计算在编译时过于复杂，编译器为了避免编译时间过长或者内存消耗过大，终止了计算。
    constexpr auto ANS = fibonacci(ANS_N);
    //auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}


/*
constepr 用于指定变量、函数或对象的值可以在编译期确定，并且在某些情况下强制在编译期执行计算。
它的主要目的是提高性能，通过将常量值的计算移到编译阶段，从而避免运行时的开销，同时增强代码的类型安全性和表达能力。

1. 修饰函数时，表示该函数可以在编译期被计算（如果所有参数也是编译期常量）。编译器会尝试在编译期计算函数的结果。 

*/
