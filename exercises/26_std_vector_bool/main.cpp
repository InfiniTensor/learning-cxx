#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);                      // 创建一个包含100个true的vector
    ASSERT(vec[0], "Make this assertion pass.");           // vec[0]应该是true
    ASSERT(vec[99], "Make this assertion pass.");          // vec[99]应该是true
    ASSERT(vec.size() == 100, "Make this assertion pass.");// 大小应该是100

    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 32, "Fill in the correct value.");// 根据实际输出修改为32

    {
        vec[20] = false;                                     // 将第21个元素设置为false
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");// 现在vec[20]是false
    }

    {
        vec.push_back(false);                                   // 添加一个false元素
        ASSERT(vec.size() == 101, "Fill in the correct value.");// 大小现在是101
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");// 新元素是false
    }

    {
        auto ref = vec[30];                     // 获取第31个元素的引用（实际上是代理对象）
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 初始时应该是true
        ref = false;                            // 通过代理对象修改值
        ASSERT(!ref, "Fill in `ref` or `!ref`");// 现在ref应该是false
        // THINK: WHAT and WHY?
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");// vec[30]也被修改为false
    }

    return 0;
}