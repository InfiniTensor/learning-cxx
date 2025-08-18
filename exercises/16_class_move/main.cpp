#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;  // 动态缓存数组
    int cached;     // 已预计算的项数（索引0~cached-1已就绪）

public:
    // 1. 动态容量构造器：分配缓存+初始化斐波那契起始值
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;  // 斐波那契第0项
        cache[1] = 1;  // 斐波那契第1项
    }

    // 2. 移动构造器：窃取源对象资源，避免深拷贝（核心：源对象放弃资源所有权）
    DynFibonacci(DynFibonacci &&other) noexcept 
        : cache(other.cache), cached(other.cached) {
        other.cache = nullptr;  // 源对象置空，避免析构时重复释放
    }

    // 3. 移动赋值运算符：处理自移动+释放当前资源+窃取源对象资源
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        // 关键：处理自移动（如fib0 = std::move(fib0)），避免释放自身资源后窃取
        if (this == &other) {
            return *this;
        }
        delete[] cache;  // 释放当前对象原有缓存，避免内存泄漏
        // 窃取源对象资源
        cache = other.cache;
        cached = other.cached;
        // 源对象置空，避免析构时重复释放
        other.cache = nullptr;
        return *this;
    }

    // 4. 析构器：释放动态缓存（delete[] nullptr安全，无需额外判断）
    ~DynFibonacci() {
        delete[] cache;
    }

    // 5. 非const版本operator[]：按需扩展缓存，支持计算未缓存的斐波那契项
    size_t operator[](int i) {
        // 循环条件：已缓存项数 <= 目标索引i，继续计算到第i项
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;  // 移动后cache为nullptr，返回false
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);  // 自移动，需安全处理
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}