#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>
/*
std::transform 是 C++ STL 中的算法函数，用来把一个范围内的元素依次映射（转换）为另一个值。
std::transform(input.begin(), input.end(), output.begin(), [](auto x){ return x * 2; });
等价于：
for (int i = 0; i < input.size(); ++i)
    output[i] = transform_function(input[i]);
高效、简洁、适用于数据管道式处理的思想，非常符合现代系统设计中对可组合、声明式的偏好。
/*
std::vector::begin() 返回一个指向 vector 容器开头的迭代器。
这个迭代器可以配合算法（如 std::transform, std::sort, std::accumulate 等）一起使用。
std::vector<int> v{1, 2, 3};
auto it = v.begin();  // it 指向第一个元素 1
迭代器的好处：
    不依赖下标索引；
    可以统一操作任何容器（vector, list, deque…）；
    与算法函数完美配合，提升抽象性与性能。
*/
int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    // std::vector<std::string> ans
    std::vector<std::string> ans(val.size());  

    std::transform(val.begin(), val.end(), ans.begin(), [](int x){ // [捕获列表](参数列表) -> 返回类型 {函数体}
        // val.begin() 和 val.end() 就是调用了 std::vector::begin() 和 std::vector::end()。
        // val.begin() === std::vector::begin()是调用 val 这个 vector 的 begin() 方法（即 STL 容器的成员函数），并返回一个迭代器（iterator），用作 std::transform 的输入范围。
        return std::to_string(x * 2); // lambda 
        // std::transform(输入开始, 输入结束, 输出开始, 变换函数);
        // 每次把输入元素 x 传给 lambda：[](int x) { return std::to_string(x * 2); });
    });

    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
