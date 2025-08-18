#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;  // 动态分配的缓存数组
    int cached;     // 已缓存的项数

public:
    // 实现动态设置容量的构造器
    // 分配capacity大小的缓存空间，并初始化前两项
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;  // 斐波那契第0项
        cache[1] = 1;  // 斐波那契第1项
    }

    // 实现析构器，释放动态分配的缓存空间
    // 遵循RAII原则：对象销毁时自动释放资源
    ~DynFibonacci() {
        delete[] cache;  // 释放动态数组
    }

    // 实现缓存优化的斐波那契计算
    size_t get(int i) {
        // 循环条件：当已缓存项数小于等于目标索引时，继续计算
        // 确保计算到目标索引i为止
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];  // 返回缓存的计算结果
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);  // 创建缓存容量为12的实例
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
