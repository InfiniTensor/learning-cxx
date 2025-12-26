#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    // 调用std::transform执行转换
    std::vector<std::string> ans(val.size());
    std::transform(
        val.begin(),  // 输入范围起始迭代器（val的第一个元素）
        val.end(),    // 输入范围结束迭代器（val的最后一个元素的下一个位置）
        ans.begin(),  // 输出范围起始迭代器（ans的第一个元素）
        [](int x) {   // lambda表达式：接收int，返回std::string
            return std::to_string(x * 2);  // 先×2，再转换为字符串
        }
    );
    // std::cout<<"ans: "<<ans<<std::endl;
    // // 打印转换后的结果
    // for (const auto& s : ans) {
    //     std::cout << s << " ";
    // }
    // std::cout << std::endl;
    // std::vector<std::string> ans
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
