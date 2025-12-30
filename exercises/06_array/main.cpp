#include "../exercise.h"

// READ: 数组 <https://zh.cppreference.com/w/cpp/language/array>

// unsigned long long这是数据类型，表示无符号的 64 位整数。unsigned 意味着它不能表示负数，而 long long 是一个通常用于表示较大整数的类型。unsigned long long 可以存储更大的非负整数，范围通常为 0 到 2^64 − 1。
// arr[90]这是定义了一个包含 90 个元素 的数组，数组名是 arr。数组中的每个元素都是类型为 unsigned long long 的整数。
unsigned long long arr[90]{0, 1}; 
// unsigned long long arr[90]{0, 1}; 声明了一个包含 90 个元素的数组，并且使用了数组的初始化语法。练习中需要理解数组如何存储和管理数据，尤其是在递归的情况下如何缓存计算结果（通过 arr 数组）。
/*
{0, 1}:

    这是数组的 初始化列表，它为数组的前两个元素赋值：

        arr[0] = 0（第一个元素被初始化为 0）

        arr[1] = 1（第二个元素被初始化为 1）

    对于数组中的其余元素（从 arr[2] 到 arr[89]），它们将被自动初始化为 0，因为 C++ 中静态数组如果没有完全初始化，其剩余元素会被默认设置为零。
*/
/*
函数外部（全局变量）：

    如果一个数组（或变量）是定义在函数外部的，那么它是全局变量，可以被程序的任何地方访问。
    它的作用域是程序中的任何地方。

    例如，arr[90] 是全局数组，它的作用域是整个程序。
*/
/*
不是纯函数。虽然它可能对相同的输入返回相同的输出，
但它依赖于一个全局变量（arr[90]）作为缓存，而全局变量会影响外部状态。
修改全局变量并不是纯函数的行为，因此它不是纯函数。
*/
unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            // TODO: 补全三目表达式缺失的部分
            //return <condition> ? <cache> : (arr[i] = fibonacci(i - 1) + fibonacci(i - 2));
            return (arr[i] != 0) ? arr[i] : (arr[i] = fibonacci(i - 1) + fibonacci(i - 2)); // 2. 使用递归实现 Fibonacci 数列，并结合 arr 数组进行记忆化优化。通过检查 arr[i] 是否为零来避免重复计算，提高了算法效率。
    }
    // Fibonacci 数列的递归算法通常效率较低（时间复杂度较高），但通过使用记忆化技术（存储已经计算的结果），该代码将计算效率大大提高。这个练习强调了如何通过优化技术改进递归算法的性能。
}

int main(int argc, char **argv) {
    // TODO: 为此 ASSERT 填写正确的值
    //ASSERT(sizeof(arr) == ?, "sizeof array is size of all its elements");
    ASSERT(sizeof(arr) == 90 * sizeof(unsigned long long), "sizeof array is size of all its elements");
    // 在 ASSERT(sizeof(arr) == 90 * sizeof(unsigned long long), "sizeof array is size of all its elements"); 语句中，考察了数组的大小如何计算。理解数组的内存大小，以及如何确保数组大小正确。
    // ---- 不要修改以下代码 ----
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1"); // 通过断言来进行单元测试和验证算法正确性。
    ASSERT(fibonacci(20) == 6765, "fibonacci(20) should be 6765");
    ASSERT(fibonacci(80) == 23416728348467685, "fibonacci(80) should be 23416728348467685");
    return 0;
}
