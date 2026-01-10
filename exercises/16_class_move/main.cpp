#include "../exercise.h"
#include <utility>

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

public:
    // TODO 1: 构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]{0, 1}), cached(2) {}

    // TODO 2: 移动构造器 (删掉 = delete)
    DynFibonacci(DynFibonacci &&other) noexcept 
        : cache(std::exchange(other.cache, nullptr)),
          cached(std::exchange(other.cached, 0)) {}

    // TODO 3: 移动赋值 (删掉 = delete)
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            delete[] cache;
            cache = std::exchange(other.cache, nullptr);
            cached = std::exchange(other.cached, 0);
        }
        return *this;
    }

    // TODO 4: 析构器
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO 5: 修复循环
    size_t operator[](int i) {
        for (; cached <= i; ++cached) { // 把 false 改成 cached <= i
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
        return cache;
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
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
