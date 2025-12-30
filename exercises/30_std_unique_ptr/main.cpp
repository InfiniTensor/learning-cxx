#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>
/*
核心考察点是理解 std::unique_ptr 资源的生命周期与析构过程，以及传递（移动）智能指针时对象的状态变化，
结合析构函数中记录字符串 _records 以 'r', 'd', 'f' 代表不同操作记录资源的生命周期。
*/

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records); 
        /*
        当 Resource 对象析构时，将 _records 追加到全局 RECORDS 中。
        */
    }
};

/*
reset/drop/forward 三个函数接受并返回 Unique（std::unique_ptr<Resource>）：
    reset 记录 'r'，返回新 Resource。
    drop 记录 'd'，返回空指针（销毁当前对象）。
    forward 记录 'f'，返回原指针。
*/
using Unique = std::unique_ptr<Resource>;
/*
reset(ptr)	如果 ptr 不为空，则对其记录 'r'，然后丢弃并返回新的 Resource 对象
drop(ptr)	如果 ptr 不为空，则对其记录 'd'，然后销毁资源，返回 nullptr
forward(ptr)	如果 ptr 不为空，则记录 'f'，并返回同一个 ptr（不修改指针）
每个 Resource 对象在被销毁时，会将其记录字符串 _records 推入全局 RECORDS 向量，形成一个 std::string。
*/
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

    // problems[0]
    {
        RECORDS.clear();
        auto r0 = reset(nullptr);
        auto f0 = forward(std::move(r0));
        auto d0 = drop(std::move(f0));
        problems[0] = std::move(RECORDS);
    }

    // problems[1]
    {
        RECORDS.clear();
        auto r1 = reset(nullptr);
        auto f1 = forward(std::move(r1));
        auto f2 = forward(std::move(f1));
        auto r2 = reset(std::move(f2));
        auto d1 = drop(std::move(r2));
        auto f3 = forward(std::move(d1));
        problems[1] = std::move(RECORDS);
    }

    // problems[2]
    {
        RECORDS.clear();
        auto r3 = reset(nullptr);
        auto r4 = reset(std::move(r3));
        auto d2 = drop(std::move(r4));
        auto r5 = reset(nullptr);
        auto d3 = drop(std::move(r5));
        auto d4 = drop(nullptr);
        problems[2] = std::move(RECORDS);
    }

    std::vector<const char *> answers[] {
        {"fd"},
        {"ffr", "d"},
        {"r", "d", "d"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        std::cout << "problems[" << i << "].size(): " << problems[i].size() << std::endl;
        std::cout << "answers[" << i << "].size(): " << answers[i].size() << std::endl;
        std::cout << "problems[2].size() = " << problems[2].size() << std::endl;
        std::cout << "answers[2].size() = " << answers[2].size() << std::endl;
        std::cout << "Adding answer #" << i << " to answers[2]\n";

        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) { 
            std::cout << "problems[" << i << "][" << j << "]: \"" << problems[i][j] << "\", length: " << problems[i][j].size() << '\n';
            std::cout << "answers[" << i << "][" << j << "]: \"" << answers[i][j] << "\", strlen: " << std::strlen(answers[i][j]) << '\n';
            if (std::strcmp(problems[i][j].c_str(), answers[i][j]) != 0) {
                std::cout << ">>> Mismatch detected!\n";
            }
            std::cout << "Comparing problems[" << i << "][" << j << "]: \"" << problems[i][j] << "\" with answers[" << i << "][" << j << "]: \"" << answers[i][j] << "\"\n";
            //遍历 problems[i] 中的每个元素。这里假设 problems 是一个二维的 std::vector<std::string>，也就是 problems[i] 是一个字符串组成的向量。
            std::cout << "Comparing problems[" << i << "][" << j << "]: " << "\"" << problems[i][j] << "\" vs \"" << answers[i][j] << "\"" << std::endl;
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location"); 
            // 逐个比较 problems[i] 与 answers[i] 中的字符串元素是否一致。
            /*
            这行的作用是断言判断：problems[i][j].c_str()：把 std::string 转换成 const char*。
            answers[i][j]：假设是一个二维的 const char* 数组或类似结构。
            std::strcmp(...) == 0：表示两个 C 风格字符串内容完全相同。如果不相同，就触发 ASSERT 报错，并提示 "wrong location"。
            */
        }
    }

    return 0;
}
/*
decltype 用于推断表达式类型，在复杂智能指针和模板代码中避免手写冗余类型。
理解对象的生命周期及智能指针操作对性能和内存安全至关重要，尤其在高频交易系统中，避免内存泄漏和未定义行为。
这题实战考察了智能指针移动、析构调用和资源管理的理解。
*/