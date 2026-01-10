#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

int main(int argc, char **argv) {
    // 1. 构造 100 个 true
    std::vector<bool> vec(100, true);
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");

    // NOTICE: 平台相关！在 Linux/GCC 64位环境下，vector<bool> 通常是 40 字节
    // 因为它需要额外存储位偏移量 (Bit Offset)
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");

    {
        vec[20] = false;
        // 既然设为 false 了，断言就要取反 (!)
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        // 大小变成 101
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        // 新加入的是 false
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // 重点：std::vector<bool> 的 operator[] 返回的不是 bool&，
        // 而是一个代理对象 (std::vector<bool>::reference)。
        // 它像一个“遥控器”，当你修改它时，它会去修改 vector 内部那个具体的 bit。
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 此时还是 true

        ref = false; // 按下遥控器，修改内部数据
        ASSERT(!ref, "Fill in `ref` or `!ref`"); // 遥控器显示 false

        // THINK: WHAT and WHY?
        // 因为 ref 是代理引用，所以原数组也被修改了！
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}