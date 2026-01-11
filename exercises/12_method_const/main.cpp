#include "../exercise.h"
#include <iostream>

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];

    // TODO: 修改方法签名和实现，使测试通过
    // 需要添加 const 限定符，因为这个方法会在 const 对象上调用
    int get(int i) const {
        // 检查索引是否在有效范围内
        if (i >= 0 && i < 11) {
            return numbers[i];
        }
        // 如果索引越界，返回 -1 作为错误值
        return -1;
    }
};

int main(int argc, char **argv) {
    // 使用 constexpr 创建常量对象
    // 注意：这里需要双花括号进行聚合初始化
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};

    // 测试基本的斐波那契值
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;

    // 测试其他值
    std::cout << "fibonacci(0) = " << FIB.get(0) << std::endl;
    std::cout << "fibonacci(1) = " << FIB.get(1) << std::endl;
    std::cout << "fibonacci(2) = " << FIB.get(2) << std::endl;
    std::cout << "fibonacci(5) = " << FIB.get(5) << std::endl;

    return 0;
}