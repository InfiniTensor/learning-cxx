#include "../exercise.h"
#include <algorithm>// 用于std::copy
#include <stdexcept>// 用于异常处理

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;// 记录缓存容量

public:
    // 实现动态设置容量的构造器
    DynFibonacci(int capacity) : capacity(capacity),
                                 cached(1),
                                 cache(new size_t[capacity]) {
        // 检查容量是否足够
        if (capacity < 2) {
            delete[] cache;// 释放已分配的内存
            throw std::invalid_argument("Capacity must be at least 2");
        }

        // 初始化前两个斐波那契数
        cache[0] = 0;// F(0)
        cache[1] = 1;// F(1)
    }

    // 实现复制构造器 - 深拷贝
    // 不能删除，因为main函数中使用了复制
    DynFibonacci(DynFibonacci const &other) : capacity(other.capacity),
                                              cached(other.cached),
                                              cache(new size_t[other.capacity]) {
        // 复制缓存数组中的所有元素
        std::copy(other.cache, other.cache + other.capacity, cache);
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算 - 非常量版本
    size_t get(int i) {
        // 边界检查
        if (i < 0) {
            throw std::out_of_range("Index cannot be negative");
        }

        if (i >= capacity) {
            throw std::out_of_range("Index exceeds cache capacity");
        }

        // 如果请求的索引已经计算过，直接从缓存返回
        if (i <= cached) {
            return cache[i];
        }

        // 计算从 cached+1 到 i 的所有斐波那契数
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        // 更新已缓存的最大索引
        cached = i;

        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    // 常量版本 - 只能读取已缓存的值
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
        return 0;// 为了避免编译器警告，虽然ASSERT会终止程序
    }

    // 可以添加赋值运算符，但这里不是必需的
    // DynFibonacci& operator=(const DynFibonacci& other) {
    //     if (this != &other) {
    //         delete[] cache;
    //         capacity = other.capacity;
    //         cached = other.cached;
    //         cache = new size_t[capacity];
    //         std::copy(other.cache, other.cache + capacity, cache);
    //     }
    //     return *this;
    // }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");

    // 复制构造 - 这会调用复制构造函数
    // 由于fib已经计算到10，所以缓存中有F(0)到F(10)的值
    DynFibonacci const fib_ = fib;// 复制构造函数调用

    // 验证复制是否成功
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");

    // 验证常量版本的方法
    std::cout << "Original fibonacci(10) = " << fib.get(10) << std::endl;
    std::cout << "Copied fibonacci(10) = " << fib_.get(10) << std::endl;

    // 测试常量版本的边界情况
    // 下面的代码会触发ASSERT，因为常量对象不能计算新的值
    // DynFibonacci const const_fib(5);
    // std::cout << const_fib.get(3) << std::endl;  // 可以，因为3 <= 1? 不，实际上cached=1，所以会触发ASSERT
    // 需要先计算值
    DynFibonacci non_const_fib(5);
    non_const_fib.get(3);                                                  // 计算F(3)
    DynFibonacci const const_fib2 = non_const_fib;                         // 复制已计算的缓存
    std::cout << "Const fibonacci(3) = " << const_fib2.get(3) << std::endl;// 可以，因为已经缓存了

    return 0;
}