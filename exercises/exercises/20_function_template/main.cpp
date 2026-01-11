#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    // 1.25 和 2.5 的二进制表示是精确的，所以可以直接相等
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    
    // TODO: 修改判断条件使测试通过
    // 0.1 和 0.2 的二进制表示是无限循环小数，存在精度损失，相加不完全等于 0.3
    // 因此需要检查差值是否在一个很小的范围内 (epsilon)
    ASSERT(plus(0.1, 0.2) - 0.3 < 1e-6 && plus(0.1, 0.2) - 0.3 > -1e-6, "How to make this pass?");

    return 0;
}