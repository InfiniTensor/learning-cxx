#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) { /* static修饰函数，表示该函数的链接属性是内部链接。这个函数只能在本文件内被调用，不能被其他文件访问
    用于限制函数作用域，避免命名冲突*/
    static int static_ = param; /*static修饰变量，表示该变量的存储期是静态存储期。它在程序开始时被初始化，并在程序结束时销毁。static变量在函数调用之间保持其值。
    相当于函数内的全局变量，但作用域仅限于函数内部*/ 
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
