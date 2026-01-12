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
    constexpr auto ANS_N = 90;
    // constexpr auto ANS = fibonacci(ANS_N);
     auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
/*本质：constexpr 要在编译期求值，编译器会模拟函数调用并受“步骤/资源限制”约束（MSVC 的 /constexpr:steps），指数级递归很快超限导致错误。
教学意义：它把编译期求值、复杂度分析（时间/空间）与语言特性（constexpr、递归 vs 迭代/动态规划）联系起来，常用于考查对编译期/运行期边界的理解。
常见解决办法：把常量改为运行时计算；或把算法改为迭代/动态规划以降低复杂度；或调整编译器常量求值限制（不推荐长期依赖）。
扩展：还涉及整数溢出、constexpr 在不同编译器的行为差异等，都是好材料用于学习与面试题。*/