#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    std::vector<std::string> ans(5);
    // 前2个参数是输入范围，2个迭代器，第3个参数是输出位置，从这里开始存放数据
    // [](int x){...}是C++的匿名函数写法，[]表示函数内不能使用函数外的变量，[=]表示可以以值传递的方式拿所有外部变量，[&]是引用方式捕获所有外部变量，[x, &y]表示值捕获x，引用捕获y, [=, &y]表示默认值捕获，y是引用，(int x)就是传参
    // -> std::string表示返回值类型，可以不写，函数体跟命名函数一样，还有返回值
    // 用法举例还有，跟Python的lambda差不多
    // int factor = 2;
    // auto multiply = [factor](int x) -> int{return x * factor};
    // std::cout << multiply(5) << std::endl; // 输出 10
    std::transform(val.begin(), val.end(), ans.begin(), [](int x) -> std::string{
        std::stringstream ss;
        ss << x * 2;
        std::string ret;
        ss >> ret;
        return ret;
    });
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
