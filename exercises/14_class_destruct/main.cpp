#include "../exercise.h"
#include <stdexcept>// 用于异常处理

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;// 记录缓存容量

public:
    // 实现动态设置容量的构造器
    // 分配缓存空间，初始化前两个斐波那契数
    DynFibonacci(int cap) : capacity(cap), cached(1) {
        // 检查容量是否足够（至少需要2个位置存储F(0)和F(1)）
        if (cap < 2) {
            throw std::invalid_argument("Capacity must be at least 2");
        }

        // 动态分配缓存数组
        cache = new size_t[capacity];

        // 初始化前两个斐波那契数
        cache[0] = 0;// F(0)
        cache[1] = 1;// F(1)
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算
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

    // 禁止拷贝构造函数和拷贝赋值（因为管理动态内存）
    // 防止浅拷贝导致重复释放内存
    DynFibonacci(const DynFibonacci &) = delete;
    DynFibonacci &operator=(const DynFibonacci &) = delete;

    // 可以提供移动构造函数和移动赋值运算符（可选）
    // DynFibonacci(DynFibonacci&& other) noexcept
    //     : cache(other.cache), cached(other.cached), capacity(other.capacity) {
    //     other.cache = nullptr;
    //     other.cached = 0;
    //     other.capacity = 0;
    // }
};// 注意：这里需要类定义结束

int main(int argc, char **argv) {
    try {
        DynFibonacci fib(12);
        ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

        // 测试边界情况
        std::cout << "fibonacci(0) = " << fib.get(0) << std::endl;
        std::cout << "fibonacci(1) = " << fib.get(1) << std::endl;
        std::cout << "fibonacci(2) = " << fib.get(2) << std::endl;
        std::cout << "fibonacci(11) = " << fib.get(11) << std::endl;

        // 测试异常情况（取消注释可以测试）
        // DynFibonacci small_fib(1);  // 应该抛出异常
        // std::cout << fib.get(12) << std::endl;  // 应该抛出异常
        // std::cout << fib.get(-1) << std::endl;  // 应该抛出异常

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}