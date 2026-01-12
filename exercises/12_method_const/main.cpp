#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    constexpr int get(int i) const {
        return numbers[i];
    }
    void test(){}
};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}

/*
FIB 是一个 constexpr 对象，这意味着它在编译时就已经被初始化，并且是常量。编译时常量
因此，当我们调用 FIB.get(10) 时，由于 FIB 是常量，所以它只能调用常量成员函数（即被const修饰的成员函数）。
所以，我们需要将 get 方法标记为 const，以表明它不会修改对象的状态。
*/