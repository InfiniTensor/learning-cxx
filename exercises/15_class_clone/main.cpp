#include "../exercise.h"
#include <cstddef>

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;

public:
    
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(0) {
        if (capacity > 0) {
            cache[cached++] = 0;
        }
        if (capacity > 1) {
            cache[cached++] = 1;
        }
    }

    DynFibonacci(DynFibonacci const & other) : cache(new size_t[other.cached]), cached(other.cached) {
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    
    ~DynFibonacci() {
        delete[] cache;
    }

    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

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
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
