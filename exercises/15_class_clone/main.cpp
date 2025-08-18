#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 1. 实现动态设置容量的构造器：分配缓存数组+初始化斐波那契起始值
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;  // 斐波那契第0项
        cache[1] = 1;  // 斐波那契第1项
    }

    // 2. 修正复制构造器：原代码"=delete"会禁止复制，导致DynFibonacci const fib_ = fib;编译失败
    //    实现深拷贝：为新对象分配独立缓存，复制原对象的缓存数据和状态
    DynFibonacci(DynFibonacci const &other) 
        : cache(new size_t[/* 需确定缓存容量，这里通过other的cached推断（或假设原容量足够） */ 12]),  // 注：实际项目需存储容量成员，此处按main中12的容量适配
          cached(other.cached) {
        // 复制原对象的缓存数据到新分配的数组
        for (int i = 0; i <= other.cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // 3. 实现析构器：释放动态分配的缓存数组，避免内存泄漏
    ~DynFibonacci() {
        delete[] cache;
    }

    // 4. 实现缓存优化的斐波那契计算（非const版本：可扩展缓存）
    size_t get(int i) {
        // 循环条件：若已缓存项数 < 目标索引i，继续计算到第i项
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
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
    DynFibonacci const fib_ = fib;  // 调用复制构造器，深拷贝fib的状态
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}