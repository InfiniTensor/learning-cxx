#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;  // 动态分配的缓存数组
    int cached;     // 已计算的斐波那契数的个数

public:
    // 构造器：动态分配缓存空间
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 复制构造器：深拷贝缓存数组
    DynFibonacci(DynFibonacci const &other) : cache(new size_t[other.cached]), cached(other.cached) {
        // 复制 cache 数组的内容
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
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

    // 常量版本的 get 方法：仅能读取缓存中的值
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
        return 0;  // 返回值，不会到达此处，防止编译错误
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);  // 使用缓存容量为 12 的构造器
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    
    // 创建一个常量对象并验证复制构造的对象
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    
    return 0;
}
