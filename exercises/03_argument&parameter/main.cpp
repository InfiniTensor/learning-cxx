#include "../exercise.h"

// READ: <https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter>
// THINK: 参数都有哪些传递方式？如何选择传递方式？

void func(int);

int main(int argc, char **argv) {
    auto arg = 99;
    // arg 初始值为 99
    ASSERT(arg == 99, "arg should be 99");
    std::cout << "befor func call: " << arg << std::endl;

    func(arg);

    // 关键点：由于是值传递，func 内部的操作不改变 arg
    ASSERT(arg == 99, "arg should be 99");
    std::cout << "after func call: " << arg << std::endl;
    return 0;
}

void func(int param) {
    // 进入函数时，param 是 arg 的副本，值为 99
    ASSERT(param == 99, "param should be 99");
    std::cout << "befor add: " << param << std::endl;

    param += 1;

    // 修改后，副本 param 变成了 100
    ASSERT(param == 100, "param should be 100");
    std::cout << "after add: " << param << std::endl;
}