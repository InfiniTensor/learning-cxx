#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    
    // 计算元素总数
    int element_count = std::accumulate(shape, shape + 4, 1, std::multiplies<int>());
    
    // 计算字节数
    int size = element_count * sizeof(DataType);
    
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
