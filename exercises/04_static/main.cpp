#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？

// static修饰func函数，表示这个函数只在这个.cpp文件中可见
// 其作用是防止重复定义,如果在另一个.cpp文件中定义了这个函数，加上static后，这两个函数就不会冲突，编译器不会发生“重复定义”错误

// static修饰static_局部变量，其作用是`静态存储期`
// 该变量**只初始化一次**，函数在运行结束后，变量不会被销毁，而是保存在内存中
static int func(int param) {
    static int static_ = param;
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
