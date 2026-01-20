#include "../exercise.h"

// const 是运行时常量，保证对象创建后不被修改；constexpr 是编译期常量，强制值必须在编译阶段就能确定

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
    constexpr auto ANS_N = 30;  // constexpr 函数虽然能在编译期计算，但编译器对递归深度和计算复杂度有实际限制。fibonacci(90) 的递归调用呈指数级增长（约 2^90 次调用），远超编译器能处理的编译期计算极限, 修改为30可以解决问题
    constexpr auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
