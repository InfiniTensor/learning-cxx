#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;  // 类Resource的unique指针；
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');   // 如果指针存在，则存储字符'r'
    return std::make_unique<Resource>();    // 返回新指针 当 unique_ptr 变为 nullptr 时（无论是通过赋值、reset() 还是函数返回），如果它原来持有对象，那么这个对象会立即被析构。
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');          // 返回空指针，作用域结束
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');          // 返回当前指针
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr))); // Unique -> fd 
    problems[0] = std::move(RECORDS);  

    forward(drop(reset(forward(forward(reset(nullptr)))))); // ffr  d
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr)))))); //  r  d  d 
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
