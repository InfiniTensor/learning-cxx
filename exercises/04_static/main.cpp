#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) {
    static int static_ = param;                 // 局部静态变量 static_ 只有在函数首次调用时，赋值才有用，若未显式赋值，则自动为0 存储在全局静态区
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++; // a++; 先赋值再加   ++a; 先加再赋值
} //在C/C++中，使用static修饰的函数只能在定义它的源文件中调用，无法被其他文件访问，从而实现了函数的封装和作用域控制

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
