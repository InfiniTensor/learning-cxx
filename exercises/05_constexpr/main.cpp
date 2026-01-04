#include <future>

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

unsigned long long fibonacci_iterative(int i) {
    if (i < 2) {
        return i;
    }
    unsigned long long a = 0, b = 1;
    for (int j = 2; j <= i; ++j) {
        unsigned long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

unsigned long long fibonacci_async(int i, int depth = 4) {
    if (depth <= 0) {
        return fibonacci_iterative(i);
    }
    if (i < 35) {
        return fibonacci_iterative(i);
    }
    auto future = std::async(std::launch::async, fibonacci_async, i - 1, depth - 1);
    unsigned long long res2 = fibonacci_async(i - 2, depth - 1);
    return future.get() + res2;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 90;
    auto ANS = fibonacci_async(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
