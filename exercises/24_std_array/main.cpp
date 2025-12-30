#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}}; // 每个int元素占4字节，总共5个元素，所以总大小为20字节。
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values."); // 比较arr和ans数组是否相同
        // std::memcmp 是一个 C 标准库函数，用于逐字节比较两个内存块。如果这两个内存块相等，它会返回 0，否则返回非零值。
        // arr.data() 是 std::array 中数据的起始地址，ans 是 C 风格数组的地址，sizeof(ans) 指定了要比较的字节数。
        // 如果 arr 和 ans 的所有元素的字节完全相同，std::memcmp 返回 0，意味着数组内容相同。
        /*
        无论是 std::array 还是 C 风格数组，在内存中都是按顺序存储元素的。它们都使用相同的内存布局方式：
        每个 int 元素通常占 4 字节（取决于平台，但在大多数平台上，int 是 4 字节）。
        arr 和 ans 都有 5 个 int 元素，因此它们的总大小都是 5 * sizeof(int)，即 5 * 4 = 20 字节。
        类型一致：arr 和 ans 都是包含 5 个 int 元素的数组，每个元素占 4 字节。由于类型相同，它们在内存中的布局方式也完全一致。
        元素一致：arr 和 ans 中的每个元素的值都相同，具体来说，它们的元素依次是 1, 2, 3, 4, 5，并且这些元素的字节表示（即整数在内存中的存储）是相同的。
        */
    }
    {
        std::array<double, 8> arr; // 默认初始化，所有元素为0.0，每个double元素占8字节，总共8个元素，所以总大小为64字节。
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"}; 
        // arr 中存储了字符数组 "Hello, InfiniTensor!"，它包含 20 个字符和一个 \0 终止符（总共 21 个字符）。
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value."); // 比较arr和字符串是否相同
        // arr.data()会返回一个指向 arr 中第一个元素的指针，这个元素是 char 类型，即指向字符数组的指针。
        // arr.data() 返回的实际上是 arr 数组的起始位置。
        // "Hello, InfiniTensor!"是一个 C 风格字符串字面量，它表示一个以 null（即 \0）结尾的字符数组。
        /*
        std::strcmp 是一个标准库函数，用于比较两个 C 风格字符串（以 \0 结尾的字符数组）。
        std::strcmp 会逐个字符比较两个字符串，直到遇到不同字符或遇到 null 字符（\0）。
        如果两个字符串完全相同，它会返回 0；如果不相同，则返回一个非零值。
        如果它们相等，则 std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0 结果为 true，表示两个字符串内容完全相同。
        */
    }
    return 0;
}
/*
std::array 是一个模板类，在定义 std::array 时，你需要指定它存储的元素类型。例如：
std::array<int, 5> arr;  // 存储5个int类型的元素。
这里的 int 就是模板参数之一，也就是说，std::array<int, 5> 表示一个存储 int 类型元素的数组，数组的大小是 5。
通过模板，你可以明确地指定数组中存储的元素类型（在这个例子中是 int），这使得 std::array 在编译时就确定了类型。

为什么这很重要？
当你定义一个 std::array<int, 5> 时，编译器知道这个数组只会存储 int 类型的元素。
这样，编译器就能够在编译时进行类型检查，确保你没有错误地向数组中放入其他类型的元素，比如字符串或浮动类型的数值。
如果你尝试做类型不匹配的操作（例如将一个 double 类型的值存入 std::array<int, 5>），编译器会报错。

std::array 是 C++11 引入的一个标准库容器，它提供了一个固定大小的数组容器，封装了传统 C 风格数组的功能，
但具有更丰富的功能和更高的类型安全性。
主要特性：
    固定大小：
    std::array 的大小在编译时就被确定，不能动态改变。这意味着它的大小是类型的一部分，无法在运行时修改。

    与 C 风格数组的区别：
        C 风格数组的大小是在运行时定义的，而 std::array 的大小在编译时就已经固定。
        std::array 提供了更多的成员函数来简化数组操作，如 .size(), .fill(), .begin(), .end() 等。

    类型安全：
    std::array 提供了更好的类型安全性，因为它是一个类模板，可以定义任意类型的数组。编译器可以检查传入的类型和数组的大小，
    避免了 C 风格数组中可能出现的越界访问。

    内存布局：
    std::array 在内存中的存储布局与 C 风格数组相同，即连续存储。所以它与普通的 C 数组在性能上没有显著差异。

    可以使用标准算法：
    由于 std::array 满足容器的接口规范，它可以与 C++ 标准库中的算法配合使用，比如 std::sort, std::find, std::accumulate 等。
*/
