#include "../exercise.h"

// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 构造器初始化 cache 和 cached
    Fibonacci() : cached(2) { 
        cache[0] = 0; 
        cache[1] = 1; 
    }

    // 缓存优化的斐波那契计算
    size_t get(int i) {
        if (i < cached) {  // 如果缓存中已有该值，则直接返回
            return cache[i];
        }
        
        // 如果缓存没有该值，则计算并存储
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1;  // 更新已计算的缓存数目
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
