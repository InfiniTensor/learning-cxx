#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // vector<bool> 是一个空间优化的特化版本，它使用位（bit）来存储布尔值。
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    // 在 Linux x86_64 GCC (libstdc++) 环境下，std::vector<bool> 的大小通常是 40 字节。
    // 在 Windows MSVC x64 环境下，通常是 32 字节。
    // 最通用的写法是直接比较 sizeof 类型。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == sizeof(std::vector<bool>), "Fill in the correct value.");
    
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // std::vector<bool> 的 operator[] 返回一个代理对象（std::vector<bool>::reference），
        // 而不是 bool&。这个代理对象重载了赋值运算符以修改底层的位。
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        // 因为 ref 是一个指向 vec[30] 底层位的代理（引用），修改 ref 会直接修改 vec 中的内容。
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}