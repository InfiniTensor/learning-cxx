#include "../exercise.h"
#include <cmath>// 添加cmath头文件用于fabs函数

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化 - 已完成
template<typename T>
T plus(T a, T b) {
    return a + b;
}

// 添加一个辅助函数用于浮点数比较
template<typename T>
bool float_equal(T a, T b, T epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    // 对于能够精确表示的浮点数（如1.25, 2.5）可以直接用==
    // 对于不能精确表示的浮点数（如0.1, 0.2）需要用差值判断
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");

    // TODO: 修改判断条件使测试通过 - 已完成
    // 使用浮点数比较的辅助函数，设置一个合理的epsilon值
    ASSERT(float_equal(plus(0.1, 0.2), 0.3), "How to make this pass?");

    return 0;
}