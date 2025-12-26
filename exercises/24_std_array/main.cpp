#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>
/*

C++ std::array 详解
std::array 是 C++11 引入的标准容器，用于表示固定大小的数组，定义在 <array> 头文件中。它结合了 C 风格数组的高效性和 STL 容器的便利性。

基本特点
固定大小：在编译时确定大小，定义时必须指定元素类型和大小（如 std::array<int, 5>）
连续存储：元素在内存中连续存放，与 C 风格数组布局兼容
零开销抽象：性能与 C 风格数组相同，没有额外的内存开销
支持 STL 操作：可以使用迭代器、size()、empty()等 STL 容器通用方法
常用成员函数
size()：返回数组中元素的数量（编译时确定的值）
data()：返回指向内部存储数组的原始指针（可用于兼容 C 风格 API）
operator[]：访问指定索引的元素（不做边界检查）
at()：访问指定索引的元素（会做边界检查，越界抛出异常）
front()/back()：访问第一个 / 最后一个元素
与 C 风格数组的对比
优势：
自带大小信息（通过size()获取），避免了 C 风格数组 "衰减为指针" 的问题
支持迭代器，可与 STL 算法无缝配合
提供了更安全的访问方式（at()方法）
劣势：
大小必须在编译时确定，无法动态改变（这也是与std::vector的主要区别）



*/

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 5*sizeof(int), "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, 20) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 8*sizeof(double), "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 21*sizeof(char), "Fill in the correct value.");
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}
