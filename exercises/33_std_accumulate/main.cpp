#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>
// accumulate中文就是累积的意思，相对浅显的用法可以看https://blog.csdn.net/qq_40803710/article/details/80273811
// 一般来说，accumulate就是求和，但提供第4个参数，也可以做一些二元运算, std::multiplies是乘法的二元函数对象
// 前2个参数就是起止范围, 第3个参数是初始值

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储的张量占用的字节数，所以初始值不是1而是用4来乘
    int size = std::accumulate(shape, shape + sizeof(shape) / sizeof(shape[0]), sizeof(float), std::multiplies<int>());
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
