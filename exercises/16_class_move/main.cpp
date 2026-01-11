#include "../exercise.h"
#include <algorithm>
#include <stdexcept>

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 实现动态设置容量的构造器
    DynFibonacci(int capacity) : capacity(capacity),
                                 cached(1),
                                 cache(new size_t[capacity]) {
        if (capacity < 2) {
            delete[] cache;
            throw std::invalid_argument("Capacity must be at least 2");
        }

        cache[0] = 0;
        cache[1] = 1;
    }

    // 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        // 将被移动对象的资源指针置空，确保其析构时不会删除资源
        other.cache = nullptr;
        other.cached = 0;
        other.capacity = 0;
    }

    // 实现移动赋值
    // 注意移动到自身问题
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        // 检查自赋值：如果地址相同，则什么都不做
        if (this != &other) {
            // 释放当前对象的资源
            delete[] cache;

            // 接管其他对象的资源
            cache = other.cache;
            cached = other.cached;
            capacity = other.capacity;

            // 将被移动对象的资源指针置空
            other.cache = nullptr;
            other.cached = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算
    // 使用运算符[]代替get方法，返回引用以支持赋值
    size_t &operator[](int i) {// 修改为返回引用
        if (i < 0) {
            throw std::out_of_range("Index cannot be negative");
        }

        if (i >= capacity) {
            throw std::out_of_range("Index exceeds cache capacity");
        }

        if (i <= cached) {
            return cache[i];
        }

        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        cached = i;
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }

    // 添加复制构造函数和复制赋值运算符（禁用）
    DynFibonacci(const DynFibonacci &) = delete;
    DynFibonacci &operator=(const DynFibonacci &) = delete;
};

int main(int argc, char **argv) {
    // 测试1: 基本功能
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 测试2: 移动构造
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    // 测试3: 移动赋值
    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    // 测试自赋值
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    // 测试4: 移动后的对象可以重新使用（如果需要）
    // 注意：被移动的对象处于有效但未定义的状态
    // 通常我们会将其置于空状态
    if (!fib.is_alive()) {
        std::cout << "Original fib was moved and is now empty" << std::endl;
    }

    // 测试5: 边界情况
    DynFibonacci fib2(5);
    fib2[4] = 3;// 计算F(4)后赋值，修改返回类型为引用后可以正常工作
    ASSERT(fib2[4] == 3, "fibonacci(4) should be 3");

    // 测试常量版本
    const DynFibonacci &const_ref = fib2;
    std::cout << "fib2[3] = " << const_ref[3] << std::endl;

    return 0;
}