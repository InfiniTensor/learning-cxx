#include "../exercise.h"

static int func(int param) {
    // 只有第一次调用时，static_ 会被赋值为 param (即 5)
    // 之后的调用都会跳过这一行初始化
    static int static_ = param;
    return static_++;// 返回当前值，然后 static_ 自增 1
}

int main(int argc, char **argv) {
    // 第一次调用：static_ 初始化为 5，返回 5，随后 static_ 变为 6
    ASSERT(func(5) == 5, "static variable value incorrect");
    // 第二次调用：跳过初始化，返回 6，随后 static_ 变为 7
    ASSERT(func(4) == 6, "static variable value incorrect");
    // 第三次调用：返回 7，随后 static_ 变为 8
    ASSERT(func(3) == 7, "static variable value incorrect");
    // 第四次调用：返回 8，随后 static_ 变为 9
    ASSERT(func(2) == 8, "static variable value incorrect");
    // 第五次调用：返回 9，随后 static_ 变为 10
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}