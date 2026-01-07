#include "../exercise.h"

// READ: 数组向指针退化 <https://zh.cppreference.com/w/cpp/language/array#%E6%95%B0%E7%BB%84%E5%88%B0%E6%8C%87%E9%92%88%E7%9A%84%E9%80%80%E5%8C%96>
bool is_fibonacci(int *ptr, int len, int stride) {
    ASSERT(len >= 3, "`len` should be at least 3");

    // 我们需要检查 len 个逻辑元素，索引范围从 0 到 len-1
    // 逻辑上的第 i 个元素在内存中的位置是 ptr + i * stride
    for (int i = 0; i < len - 2; ++i) {
        // 获取逻辑上连续的三个元素
        int a = *(ptr + i * stride);
        int b = *(ptr + (i + 1) * stride);
        int c = *(ptr + (i + 2) * stride);

        // 如果不满足 a + b = c，则不是斐波那契数列
        if (a + b != c) {
            return false;
        }
    }
    return true;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    int arr0[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55},
        arr1[]{0, 1, 2, 3, 4, 5, 6},
        arr2[]{99, 98, 4, 1, 7, 2, 11, 3, 18, 5, 29, 8, 47, 13, 76, 21, 123, 34, 199, 55, 322, 0, 0};

    // 测试点分析：
    // arr2 + 2 从 4 开始，步长 2 取出：4, 7, 11, 18, 29, 47, 76, 123, 199, 322 (满足)
    // arr2 + 3 从 1 开始，步长 2 取出：1, 2, 3, 5, 8, 13, 21, 34, 55 (满足)

    // clang-format off
    ASSERT( is_fibonacci(arr0    , sizeof(arr0) / sizeof(*arr0)    , 1),         "arr0 is Fibonacci"    );
    ASSERT( is_fibonacci(arr0 + 2, sizeof(arr0) / sizeof(*arr0) - 4, 1), "part of arr0 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr1    , sizeof(arr1) / sizeof(*arr1)    , 1),         "arr1 is not Fibonacci");
    ASSERT( is_fibonacci(arr1 + 1,  3                              , 1), "part of arr1 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2    , sizeof(arr2) / sizeof(*arr2)    , 1),         "arr2 is not Fibonacci");
    ASSERT( is_fibonacci(arr2 + 2, 10                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT( is_fibonacci(arr2 + 3,  9                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2 + 3, 10                              , 2), "guard check"                  );
    ASSERT(!is_fibonacci(arr2 + 1, 10                              , 2), "guard check"                  );
    // clang-format on
    return 0;
}