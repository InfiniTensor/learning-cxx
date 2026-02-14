#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // cache = new size_t[capacity];动态初始化数组
    // 成员初始化列表（Member Initializer List）：构造函数：函数名(参数) : 成员1(初始化), 成员2(初始化) { 函数体 }
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        // 使用 delete[]：因为 cache 是用 new[] 分配的数组
        // 如果用 delete cache（没有 []），会导致未定义行为
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; this->cached <= i; ++this->cached) {
            this->cache[this->cached] = this->cache[this->cached - 1] + this->cache[this->cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
