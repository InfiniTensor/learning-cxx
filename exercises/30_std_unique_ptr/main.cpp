#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>
// unique_ptr在同一时间只有一个unique_ptr指向对象，换句话说，一个对象只能被1个unique_ptr拥有
// 只能移动，不能拷贝，移动不会释放对象，是所有权转移
// unique_ptr释放对象的情况：被另一个unique_ptr赋值、被置为nullptr、离开作用域时自动释放资源
// 释放对象指的是，销毁指向的对象（调用析构函数）、释放内存、然后unique_ptr变为nullptr

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);    // 析构的时候记录所有操作
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
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // problems[1]产生2个资源，分别记为res1和res2，首先reset(nullptr), 传入nullptr不记录，创建res1
        // 然后forward(res1), 记录f，保持返回res1
        // forward(res1), 记录f, 保持返回res1
        // reset(res1), 非nullptr, 记录r, **应该调用析构函数**，把ffr推入RECORDS, 创建res2
        // drop(res2), 记录d，把d推入RECORDS，形参ptr离开作用域，res2**应该析构**, 返回nullptr
        // forward(nullptr)，无事发生

        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        // 再细说的话就是在该编译环境下，最外层生成的对象先于内层的对象析构，所以这里要和推导顺序反着写，可能在有些编译环境下是正着写
        // 现在采用的是Windows+Xmake+MinGW, 编译器可能是临时对象在完整表达式结束后(就是一整行代码结束后)才开始销毁对象，清理顺序后进先出可以理解为栈的pop，后产生的对象先清理，先析构
        // 有些编译器可能是函数执行完后就析构对象，那样的是正向写的
        {"d", "ffr"},
        {"d", "d", "r"},
        // 对于problem[2]也是类似的，分别记为r1, r2和r3
        // 先reset(nullptr), 传入nullptr不记录，创建r1
        // 然后reset(r1), 记录r, r1死亡，**应该调用析构函数**，把r推入RECORDS，创建r2
        // drop(r2), 记录d，返回nullptr，r2死亡，调用析构函数把d推入RECORDS
        // reset(nullptr), 传入nullptr，创建r3
        // drop(r3), 记录d, 返回nullptr，r3死亡，调用析构函数把d推入RECORDS
        // drop(nullptr), 无事发生
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