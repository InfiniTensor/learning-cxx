#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
   size_t *cache;
    int capacity;  // 改为 capacity 更清晰
    int cached;    // 已计算的最大索引
    
public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): capacity(capacity), cached(1) {
        if (capacity < 2) {
            throw std::invalid_argument("Capacity must be at least 2");
        }
        cache = new size_t[capacity];
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const &other) 
        : capacity(other.capacity),
          cached(other.cached),
          cache(new size_t[other.capacity]) {      
        // 深拷贝已缓存的斐波那契数据
        for (int i = 0; i <= cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
     // const 版本，不修改缓存
  size_t get(int i) {
    if (i < 0) {
       return false;
    }
    if (i <= cached) {
        return cache[i];
    }
    
    // 扩展缓存
    for (int j = cached + 1; j <= i; ++j) {
        cache[j] = cache[j - 1] + cache[j - 2];
    }
    cached = i;  // 更新已缓存的最大索引
    return cache[i];
}

// 保留一个 const 版本用于只读访问
    size_t get(int i) const {
    if (i < 0 || i > cached) {
        return false;
    }
    return cache[i];
}
    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
   
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
