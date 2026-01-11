#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现构造器
    // 初始化缓存数组，设置前两个斐波那契数（F(0)=0, F(1)=1）
    Fibonacci() {
        cache[0] = 0;// F(0)
        cache[1] = 1;// F(1)
        cached = 1;  // 目前已经缓存到索引1
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 如果请求的索引超出了数组大小，直接返回0（或可以抛出异常，但这里简单处理）
        if (i >= 16 || i < 0) {
            return 0;
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
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    // 可以添加更多测试
    std::cout << "fibonacci(0) = " << fib.get(0) << std::endl;
    std::cout << "fibonacci(1) = " << fib.get(1) << std::endl;
    std::cout << "fibonacci(2) = " << fib.get(2) << std::endl;
    std::cout << "fibonacci(3) = " << fib.get(3) << std::endl;
    std::cout << "fibonacci(4) = " << fib.get(4) << std::endl;
    std::cout << "fibonacci(5) = " << fib.get(5) << std::endl;
    std::cout << "fibonacci(6) = " << fib.get(6) << std::endl;
    std::cout << "fibonacci(7) = " << fib.get(7) << std::endl;
    std::cout << "fibonacci(8) = " << fib.get(8) << std::endl;
    std::cout << "fibonacci(9) = " << fib.get(9) << std::endl;
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    return 0;
}