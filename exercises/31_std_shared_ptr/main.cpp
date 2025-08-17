#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");  // shared + 3 个数组元素

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared); // ptrs[2] 改指向新对象，旧控制块 -1
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;            // +1 → 2
    ptrs[1] = shared;            // +1 → 3
    ptrs[2] = std::move(shared); // 接管 shared（shared 清空），总数仍 3
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]); // 清空 ptrs[0] → 2
    ptrs[1] = std::move(ptrs[1]);     // 自我移动，无变化 → 2
    ptrs[1] = std::move(ptrs[2]);     // 合并所有权：先释放自身(-1)再接管(+0)，最终只剩 1
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();         // 再拿一份强引用 → 2
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr; // 把最后那份也清了 → 0
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();         // 对象已析构，拿不到 → 0
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
