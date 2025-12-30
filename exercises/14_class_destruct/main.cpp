#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
/*
RAII（资源获取即初始化）与析构函数的关系
RAII（Resource Acquisition Is Initialization）：

    RAII 是一种 C++ 编程实践，用于 资源管理。该原则规定，在对象生命周期内，资源的获取和释放应与对象的创建和销毁绑定。在 C++ 中，这种管理方式通常依赖于 构造函数 和 析构函数。

    RAII 的工作方式：

        在构造函数中分配资源（如动态内存、文件句柄、数据库连接等）。

        在析构函数中释放资源（如 delete、close、free 等操作）。

    通过这种方式，我们可以确保在对象销毁时，资源会被自动释放，从而避免内存泄漏和其他资源泄露问题。

析构函数（Destructor）：

    析构函数是一个特殊的成员函数，它在对象生命周期结束时自动调用，用于释放资源。

    析构函数没有返回值，且不能被显式调用。其主要作用是 清理 对象在构造期间申请的资源。
*/
class DynFibonacci {
    size_t *cache; // 动态分配的缓存空间，用于存储斐波那契数列
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 构造函数：根据容量动态分配缓存空间，初始化cache和cached
    // DynFibonacci(int capacity): cache(new ?), cached(?) {}
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(1) {
        // 初始化前两个斐波那契数
        cache[0] = 0; // 第一个斐波那契数
        cache[1] = 1; // 第二个斐波那契数
    }
    
    // TODO: 实现析构器，释放缓存空间
    // 析构函数：在对象销毁时释放动态分配的内存，避免内存泄漏
    // ~DynFibonacci();
    ~DynFibonacci() {
        delete[] cache; // 释放内存
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 如果i已经计算过，直接返回缓存的值
        if (i <= cached) {
            return cache[i];
        }
        // 否则计算并缓存数列的第 i 个数
        /*for (; false; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        */
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];  // 计算斐波那契数并存储
        }
        cached = i; // 更新已缓存的最大索引
        return cache[i]; // 返回第 i 个斐波那契数
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
