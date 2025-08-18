#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    
    // 计算所有维度的乘积
    int total_elements = std::accumulate(
        std::begin(shape), std::end(shape), 1, std::multiplies<int>()
    );
    
    // 计算总字节数 = 元素个数 × 每个元素的大小
    int size = total_elements * sizeof(DataType);
    
    ASSERT(size == 602112, "1x3x224x224 x 4 = 602112");
    return 0;
}