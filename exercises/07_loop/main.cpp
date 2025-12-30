#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
// THINk: 这个函数是一个纯函数（pure function）吗？
/*
纯函数是指：

    对相同的输入始终返回相同的输出。

    不会修改外部状态（没有副作用）。
*/
/*
是纯函数。尽管cache是一个静态数组（static），它的生命周期是整个程序运行周期，
但它的作用域仍然局限于fibonacci函数。
fibonacci函数通过缓存来避免重复计算，而缓存的修改不会影响外部状态。
对于相同的输入，fibonacci总是返回相同的结果，且没有副作用，因此它是一个纯函数。
*/
// READ: 纯函数 <https://zh.wikipedia.org/wiki/%E7%BA%AF%E5%87%BD%E6%95%B0>
/*
cache 是在 fibonacci 函数内部 定义的，并且使用了 static 关键字。
static 关键字意味着这个变量在函数内部定义，
但它的生命周期和作用域是全局的——它会在整个程序运行过程中保留其值，而不会每次进入函数时重新初始化。
static 使得 cache 数组在 函数内部可见，
但它的生命周期不局限于函数调用时：只要程序运行，
cache 数组会一直保留其内容。
这样，在多个 fibonacci 函数的调用中，cache 数组能够保留之前的计算结果，避免重复计算。
*/
/*
函数内部（局部变量）：

    如果一个数组（或变量）是定义在函数内部的，那么它是局部变量。局部变量只在该函数内有效。

    但是，使用 static 关键字时，虽然它是局部变量，但它的生命周期会跨越多个函数调用，它的值会在调用之间保持。

    例如，cache[96] 是静态局部数组，作用域仅限于 fibonacci 函数，但生命周期为整个程序运行期间。
*/
static unsigned long long fibonacci(int i) {
    // TODO: 为缓存设置正确的初始值
    // static unsigned long long cache[96], cached;
    static unsigned long long cache[91]{0, 1}; // 初始化前两个斐波那契数
    // TODO: 设置正确的循环条件
    /*
    for (; false; ++cached) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
    }
    */
    for (int j = 2; j <= i; ++j) {
        cache[j] = cache[j - 1] + cache[j - 2]; // 计算斐波那契数并存储在缓存中
    }
    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
