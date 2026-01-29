#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};    // 共享指针shared_ptr

    std::weak_ptr<int> observer = shared;    // weak_ptr "当前指向同一对象的 shared_ptr 的数量"
    ASSERT(observer.use_count() == 4, "");  

    ptrs[0].reset();    // 变成nullptr并且清楚引用计数
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);   // 创建一个新的副本，原对象的旧值被销毁
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);        // 移动语义
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]); // 2
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);   
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();   // weak_ptr获取得到shared_ptr，引用计数 + 1
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");   

    shared = observer.lock();  // 得到其对应的shared_ptr
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
