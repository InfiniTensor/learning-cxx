#include "../exercise.h"
#include <string>
#include <type_traits>// 为 std::is_same_v 提供支持

int main(int argc, char **argv) {
    using namespace std::string_literals;

    // 带 s 后缀，类型是 std::string
    auto hello = "Hello"s;
    // 不带后缀，类型是 const char*
    auto world = "world";

    // 1. hello 的类型是 std::string
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");

    // 2. world 的类型是 const char* (字面量在作为表达式时退化为指针)
    ASSERT((std::is_same_v<decltype(world), const char *>), "Fill in the missing type.");

    // 3. 拼接逻辑：
    // hello (string) + ", " (const char*) -> "Hello, " (string)
    // "Hello, " (string) + world (const char*) -> "Hello, world" (string)
    // "Hello, world" (string) + '!' (char) -> "Hello, world!" (string)
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");

    return 0;
}