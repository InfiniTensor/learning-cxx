#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    // std::vector<bool> 的大小是平台相关的
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
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        /*
        为什么代理对象拷贝能修改原始值？
        std::vector<bool>::reference 内部保存了指向容器数据的指针和比特位索引，即使被拷贝，这些信息仍指向原始容器的内存。因此：
            无论 ref 是代理对象的引用（auto&）还是拷贝（auto），修改 ref 都会通过内部指针找到原始比特位并修改。
            这与普通对象的拷贝不同（普通对象拷贝修改不影响原值），是 vector<bool> 特化的特殊设计。

        std::vector<bool> 的代理对象（reference）具有 “值语义” 的表象（可拷贝），但内在行为是 “引用语义”（修改会影响原始容器）。因此，修改代理对象的拷贝会直接改变 vec[30] 的值，最终断言应为 !vec[30]。
        */
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
