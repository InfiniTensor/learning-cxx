#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;  // 动态分配的缓存数组
    int cached;     // 已计算的斐波那契数的个数

public:
    // 构造器：动态分配缓存空间
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 析构器：释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 缓存优化的斐波那契计算
    size_t get(int i) {
        if (i < cached) {  // 如果缓存中已有该值，直接返回
            return cache[i];
        }
        
        // 如果缓存没有该值，从已计算的最大值（cached）开始计算
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1;  // 更新缓存已计算的最大值
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);  // 使用缓存容量为 12 的构造器
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
