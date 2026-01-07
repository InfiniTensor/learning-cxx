#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];

    // TODO: 修改方法签名和实现，使测试通过
    // 添加 const 限定符，表示该函数不会修改结构体内部的数据
    // 只有这样，constexpr 对象 FIB 才能调用它
    int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    // FIB 是一个编译期常量对象
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};

    // 如果 get 不是 const 的，这里会报编译错误：
    // “不能将“this”指针从“const Fibonacci”转换为“Fibonacci &””
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}