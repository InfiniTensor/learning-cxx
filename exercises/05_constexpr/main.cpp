#include "../exercise.h"

// 修改后的斐波那契函数：使用迭代（动态规划）
constexpr unsigned long long fibonacci(int i) {
    if (i <= 0) return 0;
    if (i == 1) return 1;

    unsigned long long prev = 0;// F(0)
    unsigned long long curr = 1;// F(1)

    for (int n = 2; n <= i; ++n) {
        unsigned long long next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    constexpr auto ANS_N = 90;
    const auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}