#include "../exercise.h"
#include <iostream>

// READ: 运算符 <https://zh.cppreference.com/w/cpp/language/expressions#.E8.BF.90.E7.AE.97.E7.AC.A6>

int main(int argc, char **argv) {
    // 定义并初始化变量 x
    int x = 10;// 可以改成任何你喜欢的数字

    // 打印加法运算
    std::cout << x << " + " << x << " = " << x + x << std::endl;

    return 0;
}