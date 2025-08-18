#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // 修改方法签名：添加const修饰成员函数，允许constexpr/const对象调用
    // 实现逻辑：返回数组中索引i对应的元素
    int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    // constexpr对象初始化：数组已包含斐波那契数列前11项（索引0~10）
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}