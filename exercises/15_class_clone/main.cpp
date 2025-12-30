#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // DynFibonacci(int capacity): cache(new ?), cached(?) {}
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(1) {
        // 初始化前两个斐波那契数
        cache[0] = 0; // 第一个斐波那契数
        cache[1] = 1; // 第二个斐波那契数
    }
    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const &) = delete; // 复制构造器：显式删除，禁止复制
    /*
    显式删除了复制构造函数，意味着DynFibonacci对象不能被复制。
    禁止复制是因为 DynFibonacci 类内部有一个动态分配的内存（cache），如果对象被复制，
    就会导致两个对象指向同一块内存，最终可能会引发内存双重释放（double delete）的问题。
    */

    // TODO: 实现析构器，释放缓存空间
    // ~DynFibonacci();
    ~DynFibonacci() {
        delete[] cache; // 释放内存
    }
    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i <= cached) {
            return cache[i]; // 如果i已经计算过，直接返回缓存的值
        }
        /*
        for (; false; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        */
        // 计算并缓存数列的第 i 个数
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2]; // 计算斐波那契数并存储在缓存中
        }
        cached = i; // 更新已缓存的最大索引
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    // const版本的get方法
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    // DynFibonacci const fib_ = fib;
    // 使用引用来避免复制构造函数被调用
    DynFibonacci const &fib_ = fib; // 使用 const 引用来避免复制构造函数被调用
    /*
    为了避免复制构造函数被调用，fib_ 是通过 const 引用来初始化的。
    引用不会触发复制构造函数。使用引用的好处是：避免了不必要的对象复制，同时也避免了内存管理问题。
    */
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
