#include "../exercise.h"
#include <vector>

int main(int argc, char **argv) {
    // 正确创建 100 个元素，全部初始化为 true
    std::vector<bool> vec(100, true);
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");

    // NOTICE: 平台相关！
    // 你的运行结果显示在 Windows x64 下 MSVC 实现占用 32 字节
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 32, "Fill in the correct value.");// 这里改为 32

    {
        vec[20] = false;
        ASSERT(!vec[20], "vec[20] is now false");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Size increased to 101");
        ASSERT(!vec[100], "Last element is false");
    }
    {
        // 代理对象逻辑
        auto ref = vec[30];
        ASSERT(ref, "Initially it was true");
        ref = false;
        ASSERT(!ref, "Ref object is updated");

        // 核心原理：代理对象修改了底层位
        ASSERT(!vec[30], "The original vector bit is updated through the proxy reference.");
    }
    return 0;
}