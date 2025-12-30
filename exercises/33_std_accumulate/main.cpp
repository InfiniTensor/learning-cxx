#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224}; // 4D张量
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    // int size =
    // 计算总元素个数1x3x224x224 
    int num_elements = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>()); 
    /*
    std::accumulate(begin, end, init, op)
    begin: shape 数组起始
    end: shape 数组结束
    init: 初始值是 1（乘法单位元）
    op: std::multiplies<int>() 是乘法函数对象
    1 × 3 × 224 × 224 = 150528 个元素
    */  

    // 每个元素的字节数x总元素数
    int size = num_elements * sizeof(DataType); // sizeof(float) = 4 字节

    // size = 150528 × 4 = 602112 字节
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
