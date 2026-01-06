#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;  // 数据类型是 float
    int shape[]{1, 3, 224, 224};  // 张量的形状

    // 使用 std::accumulate 计算张量的元素数
    int size = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>());

    // 计算总字节数
    size *= sizeof(DataType);

    ASSERT(size == 602112, "4x1x3x224x224 = 602112");  // 验证字节数是否正确

    return 0;
}
