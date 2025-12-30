#include "../exercise.h"
#include <cmath>
#include <iomanip>

bool almost_equal(double a, double b, double epsilon = 1e-9) { 
    return std::fabs(a - b) < epsilon; // 判断两个浮点数是否近似相等
    // std::numeric_limits<double>::epsilon()。它是一个极小的正数，代表 两个相邻 double 类型浮点数之间的最小可辨差异。
}

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b; // 返回两个参数的和
}
/*
int plus(int a, int b) {
    return a + b;
}
*/

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    // ASSERT(plus(0.1, 0.2) == 0.3, "How to make this pass?"); 
    /*
    这个测试无法通过的根本原因是：
    0.1 + 0.2 != 0.3 在 二进制浮点数表示下并不成立！
    */
    std::cout << std::setprecision(20) << (0.1 + 0.2) << std::endl;  // 0.30000000000000004441
    /*
    计算机使用 二进制 表示所有数字,而很多十进制小数（如 0.1, 0.2）在二进制中是无限循环小数，不能精确表示。比如：
    0.1 在二进制近似为：0.000110011001100110011001100110011001100110011001100110100.2 也类似。当它们加在一起时，结果是一个无法用有限二进制精确表示的近似值。所以：
    std::cout << std::setprecision(20) << (0.1 + 0.2) << std::endl; 输出：0.30000000000000004441
    它非常接近 0.3，但不是严格相等。所以判断 0.1 + 0.2 == 0.3 会失败。
    */
    /*
    std::cout << std::setprecision(20) 使用了 std::setprecision 这个 I/O 操纵器。但它定义在 <iomanip> 中，如果没 #include <iomanip>，编译器找不到它。
    */
    ASSERT(almost_equal(plus(0.1, 0.2), 0.3), "How to make this pass?");

    return 0;
}
