#include "../exercise.h"
#include <cmath>  // 用于std::abs

// 函数模板化，支持多种数据类型
template <typename T>
T plus(T a, T b) {
    return a + b;
}

// 辅助函数：安全比较浮点数
template <typename T>
bool is_approx_equal(T a, T b, T epsilon = 1e-6) {
    // 对于整数类型，直接比较
    if constexpr (std::is_integral_v<T>) {
        return a == b;
    }
    // 对于浮点数类型，比较差值是否在可接受范围内
    else {
        return std::abs(a - b) < epsilon;
    }
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // 对于精确表示的浮点数可以直接比较
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    
    // 对于不能精确表示的浮点数，使用近似比较
    ASSERT(is_approx_equal(plus(0.1, 0.2), 0.3), "Use approximate comparison for floating points");

    return 0;
}
