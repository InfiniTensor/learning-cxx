#include "../exercise.h"
#include <vector>
#include <chrono> // 用于时间测量
#include <iostream>

// 张量即多维数组。连续存储张量即逻辑结构与存储结构一致的张量。
// 通常来说，形状为 [d0, d1, ..., dn] 的张量，第 n 维是 dn 个连续的元素，第 n-1 维是 dn-1 个连续的 dn 个元素，以此类推。
// 张量的步长或跨度指的是张量每个维度上坐标 +1 时，数据指针跨过的范围。
// 因此，一个连续张量，其第 n 维的步长为 1，第 n-1 维的步长为 dn，第 n-2 维的步长为 dn*dn-1，以此类推。
// 例如，一个 2x3x4 张量，其步长为 [12, 4, 1]。

// READ: 类型别名 <https://zh.cppreference.com/w/cpp/language/type_alias>
using udim = unsigned int;
// 测量第一段代码执行时间
void measureFirstMethod(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());
    udim product = 1; // 保存各个维度的步长乘积
    
    auto start = std::chrono::high_resolution_clock::now(); // 记录开始时间

    /*
    warning C4267: “初始化”: 从“size_t”转换到“int”，可能丢失数据
    for (int i = shape.size() - 1; i >= 0; --i) {
        strides[i] = product; // 当前维度的步长是之前所有维度的乘积
        product *= shape[i]; // 更新乘积，准备计算下一个维度的步长
    }
    */
    // 使用size_t 替代 int 来避免类型转换警告
    for (size_t i = shape.size(); i-- > 0;) { // 从最后一个维度开始逆向遍历
        strides[i] = product; // 当前维度的步长是之前所有维度的乘积
        product *= shape[i]; // 更新乘积，准备计算下一个维度的步长
    }

    auto end = std::chrono::high_resolution_clock::now(); // 记录结束时间
    std::chrono::duration<double> duration = end - start; // 计算持续时间
    std::cout << "First method took " << duration.count() << " seconds." << std::endl;
}
// 测量第二段代码的执行时间
void measureSecondMethod(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());
    udim product = 1;

    auto start = std::chrono::high_resolution_clock::now();  // 记录开始时间

    // 第二段代码：使用逆向迭代器来计算步长
    auto idx = strides.rbegin();  // 迭代器从 strides 最后一个元素开始
    for (auto it = shape.rbegin(); it != shape.rend(); ++it) { 
        *idx = product;  // 更新当前维度的步长
        product *= *it;  // 更新累积乘积
        ++idx;  // 迭代
    }

    auto end = std::chrono::high_resolution_clock::now();  // 记录结束时间
    std::chrono::duration<double> duration = end - start;   // 计算持续时间

    std::cout << "Second method execution time: " << duration.count() << " seconds\n";
}


/// @brief 计算连续存储张量的步长
/// @param shape 张量的形状
/// @return 张量每维度的访问步长
std::vector<udim> strides(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());
    udim product = 1; // 保存各个维度的步长乘积
    /*
    在代码中，udim 是一个类型别名（typedef 或 using），表示 unsigned int，即无符号整数类型。
    具体来说，它用于表示张量的步长（stride）和形状（shape）的维度，确保这些值是无符号整数，因为步长和维度通常是非负的。
    using udim = unsigned int;
    */
    // TODO: 完成函数体，根据张量形状计算张量连续存储时的步长。
    // READ: 逆向迭代器 std::vector::rbegin <https://zh.cppreference.com/w/cpp/container/vector/rbegin>
    //       使用逆向迭代器可能可以简化代码
    /*
    步长计算原理：
    张量是多维的数组。每个维度的步长是指在该维度上坐标增加 1 时，数据指针需要跨越的内存位置。
    对于一个张量，最后一个维度的步长是 1，因为它的元素是连续存储的。
    对于倒数第二个维度，它的步长等于该维度大小（即该维度元素的个数），因为每增加 1 个元素，指针会跳过整个最后一个维度的大小。
    依此类推，步长是各个维度后面维度大小的累积乘积。

    解决方案：
    从最后一维开始计算步长。
    计算每一维的步长，更新累积的步长。
    */
    // 逆向遍历每个维度，计算步长
    /*代码也可以pass
    for (int i = shape.size() - 1; i >= 0; --i) {
        strides[i] = product; // 当前维度的步长是之前所有维度的乘积
        product *= shape[i]; // 更新乘积，准备计算下一个维度的步长
    }
    */
    // 使用逆向迭代器来计算步长
    auto idx = strides.rbegin(); // 迭代器从strides最后一个元素开始
    for (auto it = shape.rbegin(); it != shape.rend(); ++it) { 
        *idx = product; // 更新当前维度的步长
        product *= *it;  // 更新累积乘积
        ++idx; 
    }

    return strides;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    // 定义测试形状（张量的维度）
    std::vector<udim> shape{2, 3, 4}; // 形状为 [2, 3, 4] 的张量

    ASSERT((strides({2, 3, 4}) == std::vector<udim>{12, 4, 1}), "Make this assertion pass.");
    /*
    {2, 3, 4} 对应的步长应该是 {12, 4, 1}：
    最后一个维度的步长是 1（因为 4 个元素是连续的）。
    第二个维度的步长是 4（因为每增加 1 个元素，要跨过 4 个元素）。
    第一个维度的步长是 12（因为每增加 1 个元素，要跨过 3 * 4 = 12 个元素）。
    */
    ASSERT((strides({3, 4, 5}) == std::vector<udim>{20, 5, 1}), "Make this assertion pass.");
    ASSERT((strides({1, 3, 224, 224}) == std::vector<udim>{150528, 50176, 224, 1}), "Make this assertion pass.");
    /*
    在 CNN（卷积神经网络） 中，图像通常表示为一个 4D 张量 [batch_size, channels, height, width]，其中 batch_size 表示批大小，
    channels 表示图像的通道数（例如，RGB 图像有 3 个通道），height 和 width 表示图像的尺寸。卷积操作通常会在图像的每个局部区域进行计算，步长在这里起着至关重要的作用。

    步长的作用：通过计算步长，卷积层可以确定如何从原始图像中提取特征（滑动窗口的大小、位置等）。
    在内存中，步长帮助快速定位图像的每个局部区域（如 3x3 的卷积核在图像上的滑动位置），以便进行卷积计算。

    假设张量的形状为 [1, 3, 224, 224]，这意味着我们有一个大小为 1x3x224x224 的 4D 张量：
    1: 批次大小（batch size）
    3: 通道数（例如 RGB 图像有 3 个通道）
    224: 图像的高度（224 像素）
    224: 图像的宽度（224 像素）
    
    步长的计算方法：
    最后一个维度（宽度 224）：这个维度的步长是 1，因为每增加一个像素，内存指针需要跳过 1 个元素。
    倒数第二个维度（高度 224）：这个维度的步长是 224，因为每增加一行，内存指针跳过一整行，即跳过 224 个元素。
    第三个维度（通道 3）：步长是 224 * 224 = 50176，因为每增加一个通道，指针需要跳过整个图像（224 * 224 个元素）。
    第一个维度（批次 1）：步长是 3 * 224 * 224 = 150528，因为每增加一个批次，指针需要跳过整个图像堆栈，即跳过 3 个通道和 224 * 224 个元素。

    张量 shape = {1, 3, 224, 224} 对应的步长是 [150528, 50176, 224, 1]，这是按照我们上面的计算方式得到的。
    批次维度的步长是 150528，即每增加一个批次跳过整个图像。
    通道维度的步长是 50176，即每增加一个通道跳过一个图像。
    高度维度的步长是 224，即每增加一行跳过 224 个元素。
    宽度维度的步长是 1，即每增加一个像素跳过 1 个元素。

    访问模式优化：
    通过正确计算张量的步长，程序可以根据数据的存储布局高效地读取和写入数据。
    例如，在图像处理和卷积神经网络（CNN）中，图像数据通常以 [batch_size, channels, height, width] 的形状存储，
    利用步长可以直接找到每个元素在内存中的地址，从而避免不必要的内存访问。
    
    作用：
    数据提取：利用步长，可以高效地从存储中提取数据。例如，假设你有一个大型数据集（比如多个图像组成的批次），可以使用步长来高效地按批次或通道读取数据，避免了不必要的内存跳转。
    并行计算：步长的计算有助于优化数据在 CPU/GPU 上的访问顺序，从而提高计算效率。高效的数据访问模式是并行计算的基础，尤其是在深度学习中。

    总结：
    ASSERT((strides({1, 3, 224, 224}) == std::vector<udim>{150528, 50176, 224, 1}) 的计算是对张量内存布局和步长的验证。步长是从最后一个维度开始逐步计算的，
    它帮助我们高效地在内存中定位元素，并确保我们能够快速访问所需的数据。
    */
    ASSERT((strides({7, 1, 1, 1, 5}) == std::vector<udim>{5, 5, 5, 5, 1}), "Make this assertion pass.");
    
    // 测量第一段代码的执行时间
    measureFirstMethod(shape);

    // 测量第二段代码的执行时间
    measureSecondMethod(shape);

    return 0;
}

/*
逆向迭代器（reverse_iterator）是 C++ 中的一个迭代器类型，它可以反向遍历容器中的元素。
与正常的迭代器（从容器的前端到尾端）不同，逆向迭代器是从容器的尾部开始遍历，逐个访问元素直到容器的起始位置。
#include <vector>
#include <iostream>
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
5 4 3 2 1

为什么使用逆向迭代器可能可以简化代码？
在计算张量的步长时，从最后一维开始逐步计算步长。逆向迭代器正好提供了这种“从尾到头”的遍历方式，避免了手动倒序操作，可以直接按照所需顺序遍历容器的元素。
简化的原因：
    自然顺序：张量步长是从最后一维到第一维进行计算的，逆向迭代器正好提供了这种逆序的遍历方式，避免了反向索引等繁琐操作。
    代码简洁：使用逆向迭代器可以使代码更简洁，不需要手动计算索引或者反向遍历。
std::vector<udim> strides(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());
    udim product = 1;

    int idx = 0;
    for (auto it = shape.rbegin(); it != shape.rend(); ++it) {
        strides[idx] = product;
        product *= *it;  // 更新累积乘积
        ++idx;
    }

    return strides;
}

*/