#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr >
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr >

int main(int, char**) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "");   // 三份有效 shared_ptr

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);            // 自移动，无变化
    ptrs[1] = std::move(ptrs[2]);            // 把 ptrs[2] 移给 ptrs[1]
    ASSERT(observer.use_count() == 2, "");   // 只剩 ptrs[1] 一份

    for (auto &p : ptrs) p = nullptr;        // 全部清空
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();                // 已过期，返回空
    ASSERT(observer.use_count() == 0, "");   // ← 关键修正

    return 0;
}