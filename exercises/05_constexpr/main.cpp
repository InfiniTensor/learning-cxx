#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    if (i < 2) return i;
    long long prev = 1, pprev = 0;
    long long cur = 0;
    for(int j = 2; j <= i; j++){
        cur = prev + pprev;
        pprev = prev;
        prev = cur;
    }
    return cur;

}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20); 
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 90;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
