#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    // int size =
    
    int elemt_count = std::accumulate(std::begin(shape),std::end(shape),1,std::multiplies<int>());
    int size = sizeof(DataType)*elemt_count;
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}


/*

accumulate( InputIt first, InputIt last, T init );

accumulate( InputIt first, InputIt last, T init, BinaryOp op );

- first last 迭代器
- init 作为累积计算的初始值，与返回类型相同的类型
- op 操作符
*/