#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// std::array是对 C 语言风格数组（如 int arr[5]）的现代化封装。
// - 既保留了原生数组的高性能（零开销）
// - 又提供了类似 STL 容器（如 std::vector）的安全性和便利性接口。
// 1.基本语法，需要包含头文件 <array>。
// - std::array<int, 5> myArray = {1, 2, 3, 4, 5};
// - 第一个模板参数 int 是数据类型，第二个模板参数 5 是数组大小（必须是编译期常量）。
// 2.为什么要使用 std::array?
// - std::array 是一个对象，包含长度消息和数据，不会退化为指针
// - std::array 支持直接赋值，只要类型和大小相同
// - std::array 安全性高，提供了 .at() 方法，会进行边界检查。如果越界，会抛出异常
// - std::array STL兼容性强，提供了迭代器（begin(), end()），可以完美配合 std::sort, std::for_each 等标准算法使用。
// 3. 主要特性
// - 内存分配： 与 C 数组一样，数据通常存储在栈（Stack）上（除非它是全局变量或被 new 出来的）。这意味着没有动态内存分配（堆内存）的开销，速度极快。
// - 固定大小： 大小在编译时必须确定，运行时不能改变（不能像 vector 那样 push_back）。
// - 零开销： 在优化开启的情况下，std::array 的性能与 C 风格数组完全一致。

// std::memcmp (Memory Compare) 是用来比较两块内存区域的内容是否完全一致的函数
// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");//数组大小
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");//int 的大小为 4
        int ans[]{1, 2, 3, 4, 5};
        //比较arr.data 和 ans，长度为 sizeof(ans)
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");     
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");//double 的大小为 8
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");//char 的大小为 1
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}
