#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;
    auto world = "world";
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // `decltype`意为 "declare type"（声明类型）
    // - 在编译期推导一个表达式或变量的类型，但不会实际计算表达式的值。
    // - int a = 10;
    // - decltype(a) b = 20; // b 的类型是 int，因为 a 是 int
    // - auto add(int x, double y) -> decltype(x + y); // 推导出返回类型为 double

    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    // std::is_same_v 是 C++17 引入的一个模板常量（属于 <type_traits> 头文件）。
    // - 用于在编译期判断两个类型是否完全相同。
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}
