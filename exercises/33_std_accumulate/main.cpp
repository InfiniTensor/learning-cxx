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
    // 初始值设为 sizeof(DataType) (也就是 4)，然后依次乘上 shape 里的每一个数
    // lambda 表达式 [](int a, int b) { return a * b; } 定义了乘法操作
    int size = std::accumulate(shape, shape + 4, sizeof(DataType), [](int a, int b) {
        return a * b;
    });
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
