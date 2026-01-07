#include "../exercise.h"

// TODO: 在这里声明函数
int add(int a, int b);// <--- 添加这一行（函数原型声明）

int main(int argc, char **argv) {
    // 这里调用 add，编译器现在知道它是一个接收两个 int 并返回 int 的函数了
    ASSERT(add(123, 456) == 123 + 456, "add(123, 456) should be 123 + 456");

    auto x = 1, y = 2;
    std::cout << x << " + " << y << " = " << add(x, y) << std::endl;
    return 0;
}

// TODO: 补全函数定义
int add(int a, int b) {
    return a + b;// <--- 在这里补全逻辑
}