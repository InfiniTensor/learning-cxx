#include "../exercise.h"
#include <cmath>// 用于 std::abs

// TODO: 将这个函数模板化
template<typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 1.25 和 2.5 在二进制中可以精确表示，所以 == 成立
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");

    // TODO: 修改判断条件使测试通过
    // 0.1 + 0.2 在双精度浮点数中实际上是 0.30000000000000004
    // 我们需要判断两者的差是否足够小
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < 1e-9, "How to make this pass?");

    return 0;
}