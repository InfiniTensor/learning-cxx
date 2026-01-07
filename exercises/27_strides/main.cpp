#include "../exercise.h"
#include <vector>

using udim = unsigned int;

/// @brief 计算连续存储张量的步长
std::vector<udim> strides(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());

    // 基础情况：如果形状为空，返回空步长
    if (shape.empty()) return strides;

    // 逻辑：从最后一维向第一维遍历
    // 最后一维的步长固定为 1
    udim current_stride = 1;

    // 使用索引逆向遍历
    for (int i = shape.size() - 1; i >= 0; --i) {
        strides[i] = current_stride;
        current_stride *= shape[i];
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