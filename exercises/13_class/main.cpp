#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16]; // 用于缓存斐波那契数列
    int cached; // 用于记录当前已经缓存的斐波那契数列的最大索引

public:
    // TODO: 实现构造器
    // Fibonacci()
    // 构造器：初始化缓存和已缓存的索引
    Fibonacci() : cached(1) { // 初始化已缓存的索引为 1，表示已计算 cache[0] 和 cache[1]
        // 初始化前两个斐波那契数
        cache[0] = 0; // 第一个斐波那契数
        cache[1] = 1; // 第二个斐波那契数
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    // 获取斐波那契数列中的第 i 个数
    size_t get(int i) {
        /*
        for (; false; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        */
        // 如果i已经计算过，直接返回缓存的值
        if (i <= cached) {
            return cache[i];
        }
        // 否则计算并缓存数列的第 i 个数
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2]; // 计算斐波那契数并存储在缓存中
        }
        cached = i; // 更新已缓存的最大索引
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
