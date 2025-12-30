#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>
// constexpr使得get方法可以在编译时进行求值。它要求方法是常量表达式，因此可以在FIB对象初始化时直接求得斐波那契数列的值
// const关键字用于确保get方法不会修改成员变量，这也符合常量表达式要求
/*
CV限定符（const和 volatile）是C++中用于修饰成员函数的关键字吗，它们影响成员函数是否可以修改类的成员变量，以及成员函数如何与对象的状态交互。
具体来说，CV限定符指的是const和volatile限定符，它们分别用于指定函数和对象的行为约束。
*/
/*
编译时初始化（constexpr 或常量表达式初始化）是指 在编译时，根据已知的常量数据来计算并初始化某些值。
使用 constexpr 可以让变量或函数在 编译时就得到计算结果，而不是在 运行时 执行计算。
这种方法的作用是提高程序的效率，因为编译器会在编译过程中将常量值计算好，减少了运行时的计算开销。
*/
struct Fibonacci {
    int numbers[11]; // 存储斐波那契数列的前 11 个数
    // TODO: 修改方法签名和实现，使测试通过
    /*
    int get(int i) {
    }
    */
    // 修改方法签名，确保它是一个constexpr 成员函数
    // 这样可以在编译时计算斐波那契数列的值
    constexpr int get(int i) const {
        return numbers[i]; // 返回第 i 个斐波那契数
    }
};

int main(int argc, char **argv) {
    // constexpr对象初始化，传入前 11 个斐波那契数
    // FIB在main函数中被声明为constexpr对象，这确保了编译时常量值被正确使用。constexpr变量可以在编译时直接初始化，因此FIB.get(10) 可以在编译时返回55
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55"); // FIB.get(10) 返回第 11 个斐波那契数
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
