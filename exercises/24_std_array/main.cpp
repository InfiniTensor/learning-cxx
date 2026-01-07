#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        // int 通常占 4 字节，5 个 int 占 20 字节
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        // 使用 .data() 获取底层指针，比较长度为 5 * sizeof(int) 即 20 字节
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        // double 通常占 8 字节，8 个 double 占 64 字节
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        // char 占 1 字节，21 个 char 占 21 字节
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        // strcmp 需要底层 char* 指针
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}