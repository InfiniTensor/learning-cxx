#include "../exercise.h"

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity_;// 辅助变量，记录容量以便复制

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2), capacity_(capacity) {
        if (capacity > 0) cache[0] = 0;
        if (capacity > 1) cache[1] = 1;
    }

    // TODO: 实现复制构造器 (深拷贝)
    DynFibonacci(DynFibonacci const &other) {
        // 1. 按照对方的容量申请新内存
        capacity_ = other.capacity_;
        cached = other.cached;
        cache = new size_t[capacity_];
        // 2. 将对方缓存中的数据复制到自己的内存中
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");

    // 这里会触发复制构造函数
    DynFibonacci const fib_ = fib;

    // fib_ 是 const 对象，调用的是 const 版本的 get
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}