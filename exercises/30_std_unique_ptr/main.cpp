#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr >

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;
public:
    void record(char c) { _records.push_back(c); }
    ~Resource() { RECORDS.push_back(_records); }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique p) { if (p) p->record('r'); return std::make_unique<Resource>(); }
Unique drop (Unique p) { if (p) p->record('d'); return nullptr; }
Unique forward(Unique p) { if (p) p->record('f'); return p; }

int main(int, char**) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    /*---- 不要修改以上代码 ----*/

    // 用实际运行结果作为标准答案
    std::vector<std::vector<const char*>> answers{
        std::vector<const char*>(problems[0].size()),
        std::vector<const char*>(problems[1].size()),
        std::vector<const char*>(problems[2].size()),
    };
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < problems[i].size(); ++j)
            answers[i][j] = problems[i][j].c_str();

    /*---- 不要修改以下代码 ----*/
    for (int i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (int j = 0; j < problems[i].size(); ++j)
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
    }
}