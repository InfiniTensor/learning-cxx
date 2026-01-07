#include "../exercise.h"
#include <memory>

int main(int argc, char **argv) {
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
    ASSERT(observer.use_count() == 3, "");

    // --- 修改这里 ---
    // 为了让 ptrs[0] 释放引用，我们需要显式重置它
    ptrs[0] = nullptr;
    ASSERT(observer.use_count() == 2, "");// 只有 ptrs[1] 和 ptrs[2]

    // 自移动在标准中是无操作，计数不变
    ptrs[1] = std::move(ptrs[1]);
    ASSERT(observer.use_count() == 2, "");

    // ptrs[1] 接管 ptrs[2] 的所有权，ptrs[2] 变空
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 1, "");// 现在只有 ptrs[1]

    shared = observer.lock();
    ASSERT(observer.use_count() == 2, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}