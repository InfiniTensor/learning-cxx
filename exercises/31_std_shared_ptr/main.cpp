#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);            // shared 引用计数 = 1
    std::shared_ptr<int> ptrs[]{shared, shared, shared};// 复制3次，引用计数 = 4

    std::weak_ptr<int> observer = shared;// weak_ptr 不增加引用计数
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();// ptrs[0] 释放，引用计数 = 3
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;// ptrs[1] 置空，引用计数 = 2
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);// ptrs[2] 指向新对象，原对象引用计数 = 1
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;           // 引用计数 = 2
    ptrs[1] = shared;           // 引用计数 = 3
    ptrs[2] = std::move(shared);// 移动，shared 变空，引用计数仍 = 3
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);// ptrs[0] 不变！引用计数仍 = 3
    ptrs[1] = std::move(ptrs[1]);    // 自移动（实现定义），假设不变，引用计数 = 3
    ptrs[1] = std::move(ptrs[2]);    // ptrs[1] 释放后接管 ptrs[2]，引用计数 = 2
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();// 从 weak_ptr 获取 shared_ptr，引用计数 = 2
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;                    // 引用计数 = 1
    for (auto &ptr : ptrs) ptr = nullptr;// 全部置空，引用计数 = 0，对象被销毁
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();// 对象已销毁，lock() 返回空 shared_ptr
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
