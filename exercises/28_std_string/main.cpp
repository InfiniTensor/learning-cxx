#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // 开启 "..."s 后缀功能
    using namespace std::string_literals;
    
    auto hello = "Hello"s; // 类型是 std::string
    auto world = "world";  // 类型是 const char *


    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    
  
    ASSERT((std::is_same_v<decltype(world), const char *>), "Fill in the missing type.");
    
  
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    
    return 0;
}