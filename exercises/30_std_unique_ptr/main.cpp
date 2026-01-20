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
        // std::cout << "ptr->_records: " << _records << std::endl;
    }

    ~Resource() {
        // std::cout << "~Resource(): _records: " << _records << std::endl;
        RECORDS.push_back(_records);
        // for (const auto& s : RECORDS) {std::cout << s << std::endl;}
    }
};

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

    drop(forward(reset(nullptr)));
    // std::cout << "After drop(forward(reset(nullptr)))" << std::endl;
    // for (const auto& s : RECORDS) {std::cout << s << std::endl;}
    problems[0] = std::move(RECORDS);
    // std::cout << "after problems[0] = std::move(RECORDS)" << std::endl;
    // for (const auto& s : RECORDS) {std::cout << s << std::endl;}

    forward(drop(reset(forward(forward(reset(nullptr))))));
    // std::cout << "After forward(drop(reset(forward(forward(reset(nullptr))))))" << std::endl;
    // for (const auto& s : RECORDS) {std::cout << s << std::endl;}
    problems[1] = std::move(RECORDS);
    // std::cout << "After problems[1] = std::move(RECORDS);" << std::endl;
    // for (const auto& s : RECORDS) {std::cout << s << std::endl;}

    drop(drop(reset(drop(reset(reset(nullptr))))));
    // std::cout << "After drop(drop(reset(drop(reset(reset(nullptr))))));" << std::endl;
    // for (const auto& s : RECORDS) {std::cout << s << std::endl;}
    problems[2] = std::move(RECORDS);
    // std::cout << "After problems[2] = std::move(RECORDS);" << std::endl;
    // for (const auto& s : RECORDS) {std::cout << s << std::endl;}

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

/*
for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < problems[i].size(); j++) {
        std::cout << "i = " << i << ", j = " << j << ",problems[i][j].c_str = " << problems[i][j].c_str() << std::endl; 
    }
}
*/

// ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            // std::cout << "i = " << i << ", j = " << j << ", problems[i][j].c_str = " << problems[i][j].c_str() << ", answers[i][j] = " << answers[i][j] << std::endl;
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
