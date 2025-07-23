#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

/**
关键知识点解释
    1.use_count() 的含义
        std::weak_ptr::use_count() 返回当前观察对象的 std::shared_ptr 数量。weak_ptr 本身不增加引用计数。
    2.引用计数变化分析
        初始状态：shared 和 ptrs 中的 3 个 shared_ptr 共 4 个引用。
        逐步释放：每次释放一个 shared_ptr，引用计数减 1。
        移动语义：std::move 转移所有权，原 shared_ptr 变为空，引用计数不变。
        lock()：当对象存在时，observer.lock() 创建新的 shared_ptr，引用计数加 1；对象不存在时返回空指针。
    3.特殊操作
        ptrs[2] = std::make_shared<int>(*shared)：创建新对象并赋值给 ptrs[2]，原对象引用计数减 1。
        ptrs[1] = std::move(ptrs[1])：自移动无实际效果，ptrs[1] 保持不变。

 总结
    shared_ptr 的引用计数反映了对象的存活状态。
    weak_ptr 用于观察 shared_ptr 管理的对象，不影响引用计数。
    通过 lock() 可从 weak_ptr 创建 shared_ptr，需检查对象是否已销毁。
*/

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;// weak_ptr观察shared_ptr
    ASSERT(observer.use_count() == 4, "初始时shared_ptr有4个：shared和ptrs中的3个");

    ptrs[0].reset();// 释放ptrs[0]
    ASSERT(observer.use_count() == 3, "释放ptrs[0]后，剩余3个shared_ptr");

    ptrs[1] = nullptr;// 释放ptrs[1]
    ASSERT(observer.use_count() == 2, "释放ptrs[1]后，剩余2个shared_ptr");

    ptrs[2] = std::make_shared<int>(*shared);// ptrs[2]指向新对象
    ASSERT(observer.use_count() == 1, "ptrs[2]指向新对象后，原对象只剩shared");

    ptrs[0] = shared;           // ptrs[0]重新指向shared
    ptrs[1] = shared;           // ptrs[1]重新指向shared
    ptrs[2] = std::move(shared);// ptrs[2]通过移动语义获取shared的所有权，shared变为空
    ASSERT(observer.use_count() == 3, "ptrs[0]、ptrs[1]和ptrs[2]指向原对象，shared为空");

    std::ignore = std::move(ptrs[0]);// 移动ptrs[0]到std::ignore，ptrs[0]变为空
    ptrs[1] = std::move(ptrs[1]);    // 自移动，无实际效果
    // ptrs[1] = std::move(ptrs[2]) 后，ptrs[1] 持有资源，ptrs[2] 为空，但原对象的引用计数未减少（只是所有权转移）。
    // 此时原对象的 shared_ptr 有 ptrs[1] 和 ptrs[2]（转移前的），共 2 个。
    ptrs[1] = std::move(ptrs[2]);// ptrs[1]获取ptrs[2]的所有权
    ASSERT(observer.use_count() == 2, "ptrs[1]和ptrs[2]指向原对象");

    shared = observer.lock();  // 通过observer创建新的shared_ptr
    ASSERT(observer.use_count() == 3, "shared和ptrs[1]和ptrs[2]指向原对象");

    shared = nullptr; // 释放shared
    for (auto &ptr : ptrs) ptr = nullptr; // 释放所有ptrs
    ASSERT(observer.use_count() == 0, "所有shared_ptr被释放，对象已销毁");

    shared = observer.lock();  // 对象已销毁，lock()返回空shared_ptr
    ASSERT(observer.use_count() == 0, "对象已销毁，use_count为0");

    return 0;
}
