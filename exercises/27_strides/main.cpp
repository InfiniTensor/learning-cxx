#include "../exercise.h"
#include <vector>

using udim = unsigned int;

/// @brief 计算连续存储张量的步长
/// @param shape 张量的形状
/// @return 张量每维度的访问步长
std::vector<udim> strides(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());
    if (shape.empty()) return strides;
    
    // 从最后一个维度开始计算，最后一个维度的步长总是1
    strides[shape.size() - 1] = 1;
    // 从倒数第二个维度向前计算
    for (size_t i = shape.size() - 2; i < shape.size(); --i) {
        strides[i] = strides[i + 1] * shape[i + 1];
    }
    
    return strides;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT((strides({2, 3, 4}) == std::vector<udim>{12, 4, 1}), "Make this assertion pass.");
    ASSERT((strides({3, 4, 5}) == std::vector<udim>{20, 5, 1}), "Make this assertion pass.");
    ASSERT((strides({1, 3, 224, 224}) == std::vector<udim>{150528, 50176, 224, 1}), "Make this assertion pass.");
    ASSERT((strides({7, 1, 1, 1, 5}) == std::vector<udim>{5, 5, 5, 5, 1}), "Make this assertion pass.");
    return 0;
}