#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");   // 数组的大小
        ASSERT(sizeof(arr) == 4*5, "Fill in the correct value."); // int 4个字节 一共4*5
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.begin(), ans, sizeof(arr)) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value."); // 数组的大小
        ASSERT(sizeof(arr) == 64, "Fill in the correct value."); // double 8个字节 一共8*8
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        ASSERT(std::strcmp(arr.begin(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}

/*

int arr[5] = {1, 2, 3, 4, 5};

// arr 的类型是 int[5]（数组类型）
// &arr 的类型是 int(*)[5]（指向整个数组的指针）

int* ptr = arr;  // arr 退化为指向第一个元素的指针

*/