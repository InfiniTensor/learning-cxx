#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

/**
 * Resource类：通过record方法记录字符，析构时将记录的字符串存入全局RECORDS。
 */
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

/**
三个函数：
    reset(ptr)：若ptr非空，让其记录 'r'，返回新Resource（旧ptr被销毁）。
    drop(ptr)：若ptr非空，让其记录 'd'，返回nullptr（ptr被销毁）。
    forward(ptr)：若ptr非空，让其记录 'f'，返回ptr（所有权转移，不销毁）。
 */
using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    /**
    测试用例 1：drop(forward(reset(nullptr)))
    执行流程：
        reset(nullptr)：创建Resource A（无记录），返回A。
        forward(A)：A记录 'f'（_records = "f"），返回A。
        drop(A)：A记录 'd'（_records = "fd"），A被销毁，RECORDS = ["fd"]。
    problems[0]结果：{"fd"}（跨平台一致）。
     */
    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    /**
    测试用例 2：forward(drop(reset(forward(forward(reset(nullptr))))))
    执行流程：
        最内层reset(nullptr)：创建Resource A（无记录），返回A。
        第一次forward(A)：A记录 'f'（_records = "f"），返回A。
        第二次forward(A)：A记录 'f'（_records = "ff"），返回A。
        reset(A)：A记录 'r'（_records = "ffr"），创建Resource B，A被销毁（RECORDS暂存 "ffr"），返回B。
        drop(B)：B记录 'd'（_records = "d"），B被销毁（RECORDS暂存 "ffr", "d"），返回nullptr。
        forward(nullptr)：无操作。
    problems[1]结果：
        因A和B的析构顺序在不同平台可能不同，实际测试中macOS 和 Ubuntu 下为{"d", "ffr"}。
     */
    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    /**
    测试用例 3：drop(drop(reset(drop(reset(reset(nullptr))))))
    执行流程：
        最内层reset(nullptr)：创建Resource A（无记录），返回A。
        reset(A)：A记录 'r'（_records = "r"），创建Resource B，A被销毁（RECORDS暂存 "r"），返回B。
        drop(B)：B记录 'd'（_records = "d"），B被销毁（RECORDS暂存 "r", "d"），返回nullptr。
        reset(nullptr)：创建Resource C（无记录），返回C。
        drop(C)：C记录 'd'（_records = "d"），C被销毁（RECORDS暂存 "r", "d", "d"），返回nullptr。
        外层drop(nullptr)：无操作。
    problems[2]结果：
        因多对象析构顺序差异，macOS 和 Ubuntu 下为{"d", "d", "r"}。
     */
    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
    // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
    // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
#ifdef __APPLE__
        {"d", "ffr"},
        {"d", "d", "r"}
#elif defined(__linux__)
        {"d", "ffr"},
        {"d", "d", "r"}
#else
        {"ffr", "d"},
        {"r", "d", "d"},
#endif
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
