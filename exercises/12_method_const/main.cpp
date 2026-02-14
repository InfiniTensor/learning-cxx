#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    // int get(int i) {
    // }
    int get(int i) const {
        if (i<0 || i>=11)
        {
            return 0;
        }
        
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    //关键字 constexpr 意味着对象 FIB 是编译期常量，它隐含了 const 属性。在 C++ 中，const 对象只能调用 const 成员函数。
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
