#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s; 
    auto world = "world";
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}
/*
📘 延伸：这个知识点在高性能或交易系统中应用？

    类型推导 (decltype) 和类型判别 (std::is_same_v)：
        在模板元编程中自动推导类型，构建泛型数据结构（如订单、行情、策略对象）；
        提升类型安全，防止因类型不匹配引发性能损失或崩溃；

    在 HFT（高频交易）系统 或 AI 推理引擎（如 TensorRT） 中，常用于：
        模板代码中自动判断数据结构兼容性；
        静态分支优化：只有当类型满足某条件时才启用某些 SIMD 路径。
*/