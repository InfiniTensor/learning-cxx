#include "../exercise.h"
#include <algorithm>
#include <iterator>// 包含 std::back_inserter
#include <string>
#include <vector>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};

    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    std::vector<std::string> ans;

    // 预分配空间（可选但推荐，性能更好）
    ans.reserve(val.size());

    // 执行转换
    std::transform(
        val.begin(),            // 输入起始迭代器
        val.end(),              // 输入结束迭代器
        std::back_inserter(ans),// 输出插入迭代器
        [](int x) {             // 转换 Lambda 函数
            return std::to_string(x * 2);
        });

    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");

    return 0;
}