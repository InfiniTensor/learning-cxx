#include "../exercise.h"
#include <string>

int main(int, char**) {
    using namespace std::string_literals;
    auto hello = "Hello"s;          // 后缀 s → std::string
    auto world = "world";           // 无后缀 → const char*

    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");

    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}