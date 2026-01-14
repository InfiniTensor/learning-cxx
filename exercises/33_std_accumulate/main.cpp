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
     float element_count = std::accumulate(
        std::begin(shape),    // 输入序列起始迭代器（数组首地址）
        std::end(shape),      // 输入序列结束迭代器（数组尾后地址）
        1.0f,                 // 初始值（float类型，避免整数溢出）
        std::multiplies<float>() // 累乘操作（替代默认的累加）
    );

    // 步骤2：计算总字节数 = 总元素数 × 单个元素的字节数
    int size = static_cast<int>(element_count * sizeof(DataType));
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
