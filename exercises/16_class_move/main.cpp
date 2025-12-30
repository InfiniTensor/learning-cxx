#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>
/*
👑移动语义的优势：
    减少堆内存分配/释放次数
    避免不必要的深拷贝
    提升吞吐，降低延迟
    非常适用于临时对象或中间层传递
*/
class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity; // 新增容量字段，用于记录缓存的容量

public:
    // 构造函数：初始化缓存空间并设置前两个斐波那契数
    // TODO: 实现动态设置容量的构造器
    // DynFibonacci(int capacity): cache(new ?), cached(?) {}
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(1), capacity(capacity) {
        // 初始化前两个斐波那契数
        cache[0] = 0; // 第一个斐波那契数
        cache[1] = 1; // 第二个斐波那契数
    }

    // TODO: 实现移动构造器
    // DynFibonacci(DynFibonacci &&) noexcept = delete;
    // 移动构造器：将资源从源对象转移到新对象
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr; // 将源对象的缓存指针置为 nullptr，避免析构时释放内存。移动后原对象置空
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    // DynFibonacci &operator=(DynFibonacci &&) noexcept = delete;
    // 移动赋值操作符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept { // noexcept 是C++11引入的关键词，表示函数承诺不会抛异常
        /*
        对于移动构造/移动赋值来说，加 noexcept 非常关键：
        STL 容器（如 std::vector）在扩容时，如果能确认移动操作是 noexcept，会优先用移动，而不是更昂贵的拷贝。
        否则，容器会保守地用拷贝，防止在移动中途抛异常导致程序崩溃。
        */
        if (this != &other) { // 防止自移动
            delete[] cache; // 释放当前对象的缓存内存。释放旧内存
            cache = other.cache; // 转移资源
            cached = other.cached;
            capacity = other.capacity;
            other.cache = nullptr; // 将源对象的缓存指针置为 nullptr，避免析构时释放内存，防止双重释放
        }
        return *this; // 返回当前对象的引用
    }

    // TODO: 实现析构器，释放缓存空间
    // ~DynFibonacci();
    // 析构函数：释放动态分配的内存，避免内存泄漏
    ~DynFibonacci() {
        delete[] cache; // 释放内存
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    /*
    size_t operator[](int i) {
        for (; false; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
    */
    // 获取斐波那契数列中的第 i 个数
    size_t operator[](int i) {
        ASSERT(i < capacity, "Out of bounds"); // 确保索引不超过缓存容量
        if (i > cached) {
            for (int j = cached + 1; j <= i; ++j) {
                cache[j] = cache[j - 1] + cache[j - 2]; // 计算斐波那契数并存储在缓存中
            }
            cached = i; // 更新已缓存的最大索引
        }        
        return cache[i]; // 返回第 i 个斐波那契数
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
    DynFibonacci fib(12); // 创建一个对象fib，假设它在堆上分配了Fibonacci值数组
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 第一个移动构造
    // 移动构造函数：用一个右值对象初始化一个新对象，把资源拿过来构造新对象
    DynFibonacci const fib_ = std::move(fib); // 第一个移动构造，std::move(fib)把fib转为右值引用
    /*
    如果 DynFibonacci 实现了 移动构造函数，则此处：将 fib 的内部资源（如 std::vector 或 int*）“移动”到 fib_。fib_ 成为新的拥有者。
    fib 进入“已移动”状态，通常不再使用。
    */
    ASSERT(!fib.is_alive(), "Object moved"); // 检查fib是否还拥有资源。如果实现得当，这里返回false（fib已被移动，资源已转移到fib_）
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    // 第二个移动赋值
    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    // 移动赋值运算符：把一个右值对象赋给已有对象，先释放旧资源，再拿新资源
    fib0 = std::move(fib1); // std::move() 把左值转为右值引用（不是“移动”，只是触发“可移动”），它不会移动对象本身，而是把fib1转换成右值引用
    //允许移动语义触发。换句话说，std::move告诉编译器：我允许你拿走fib1的资源
    /*
    fib0 = std::move(fib1); 触发 移动赋值运算符：fib0释放自己的资源。接收 fib1 的资源。fib1 进入“已移动”状态。
    */
    fib0 = std::move(fib0); // 自己移动给自己，会触发移动赋值，operator=(DynFibonacci &&other)，其中other实际就是*this
    // 如果类实现不当（比如未检查 this != &other），可能会释放自己的资源后再用它，导致严重错误（use-after-free）。

    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55"); // 说明 fib0 最终应拥有 fib1 的资源（其中包含 Fibonacci 第 10 项为 55）。

    return 0;
}
