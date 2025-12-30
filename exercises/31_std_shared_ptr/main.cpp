#include "../exercise.h"
#include <memory>
#include <iostream>

void print_state(const std::string& msg, const std::shared_ptr<int>& shared, std::shared_ptr<int> ptrs[], size_t size, const std::weak_ptr<int>& observer){
    std::cout << msg << "\n";
    std::cout << " observer.use_count() = " << observer.use_count() << "\n";
    std::cout << " shared.get() = " << shared.get() << "\n";
    for (size_t i = 0; i < size; ++i){
        std::cout << " ptrs[" << i << "].get() = " << ptrs[i].get() << "\n";
    }
    std::cout << "-----------------------\n";
}

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    
    auto shared = std::make_shared<int>(10); // shared是第一个shared_ptr，count=1
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // ptrs[0] = shared, count=2
    // ptrs[1] = shared, count=3
    // ptrs[2] = shared, count=4
    // ptrs数组3个元素都指向shared，引用计数增加到4

    std::weak_ptr<int> observer = shared;  // observer是一个weak_ptr，观察shared的引用计数，但不增加引用计数
    print_state("初始状态：shared和ptrs[0,1,2]都指向同一个资源", shared, ptrs, 3, observer);
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 4, ""); 

    ptrs[0].reset(); 
    print_state("ptrs[0].reset()后", shared, ptrs, 3, observer);
    std::cout << "use_count: " << observer.use_count() << "\n";
    // ptrs[0] 释放了对 shared 的引用，引用计数减少到3
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    // ptrs[1] 也释放了对 shared 的引用，引用计数减少到2
    print_state("ptrs[1]=pullptr()后", shared, ptrs, 3, observer);
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared); // ptrs[2]指向一个新对象，与原来的 shared 无关
    print_state("ptrs[2]指向新资源后", shared, ptrs, 3, observer);
    // 所以原资源引用计数从2->1
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared; // ptrs[0]重新指向原 shared_ptr，引用计数增加到2
    ptrs[1] = shared; // ptrs[1] 重新指向原 shared_ptr，引用计数增加到3
    ptrs[2] = std::move(shared); // shared变空，ptrs[2]指向原资源，引用计数不变
    print_state("ptrs[0], ptrs[1], ptrs[2] 都指向旧资源，shared 变空", shared, ptrs, 3, observer);
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 3, ""); // shared已经为空
    // use_count = 3 (ptrs[0], ptrs[1], ptrs[2])

    std::ignore = std::move(ptrs[0]);
    print_state("move ptrs[0] 后 ptrs[0] 变空", shared, ptrs, 3, observer);
    // use_count = 2
    // ptrs[0] 被移动赋值到一个空目标（std::ignore），它的资源被“吃掉”，但没人接管它的指针，直接销毁。所以引用计数 从 3 → 2。ptrs[1]和ptrs[2]
    
    ptrs[1] = std::move(ptrs[1]);
    print_state("ptrs[1] move给自己，状态没变", shared, ptrs, 3, observer);
    // ptrs[1] 自己move给自己，没变化。2。ptrs[1]和ptrs[2]

    ptrs[1] = std::move(ptrs[2]);
    print_state("ptrs[1] = std::move(ptrs[2])，ptrs[2]变空", shared, ptrs, 3, observer);
    // use_count 依旧是 2
    /*
    - ptrs[1] 原先持有资源，move前引用计数中包括ptrs[1]的1
    - ptrs[2] 持有相同资源
    - 执行移动时，ptrs[1] 先释放自己指向的资源（计数-1），
      再接管ptrs[2]指向的资源（计数+1）
    - ptrs[2] 变空（计数-1）
    - 但ptrs[1]接管了ptrs[2]的资源，计数加回1
    - 结果引用计数不变，仍然是2
    */
    /*
    把 ptrs[2] 的资源移交给 ptrs[1]，然后 ptrs[2] 变成空。实际上 ptrs[1] 原本就指向同一个资源，移过去之后旧资源销毁，新资源接管，指向的资源没变。
    所以引用计数 保持为 2。
    */
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 2, ""); 
    /*
    所以还持有资源的是：
    ptrs[1]
    observer.lock() 没调用，所以 weak_ptr 不计入 use_count
    因此 use_count == 2，包括：
    ptrs[1]（正在持有）
    原来的 shared 被 std::move() 给了 ptrs[2]，再被 move 到 ptrs[1]，但是这个 shared_ptr 的引用仍是同一个对象。

    最终 use_count == 2，持有者是：
    ptrs[1]
    ptrs[2] 之前 move 过来的资源（就是 shared 的原始资源）

    std::move(ptrs[2]) 会将 ptrs[2] 的资源（资源 A）“转移”给 ptrs[1]。
    但注意： ptrs[1] 也持有资源 A！所以流程是：
    ptrs[1] 原先持有资源 A，先调用析构，引用计数减 1（但资源还没销毁，因为 ptrs[2] 也持有）
    ptrs[1] 获得 ptrs[2] 持有的资源 A，引用计数加 1
    ptrs[2] 变成空指针，引用计数减 1
    */

    shared = observer.lock();
    print_state("shared = observer.lock() 后", shared, ptrs, 3, observer);
    // use_count = 3
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 3, "");

    // 释放所有资源
    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    print_state("释放所有资源", shared, ptrs, 3, observer);
    // use_count = 0
    // 所有 ptrs 都变成空指针，shared 也变成空指针，资源已被释放
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    print_state("资源已释放，observer.lock() 返回空", shared, ptrs, 3, observer);
    // observer.lock()返回空指针，因为资源已经被释放
    std::cout << "use_count: " << observer.use_count() << "\n";
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
/*
shared_ptr 持有对象，决定对象何时销毁
weak_ptr 不持有对象，只是观察，防止循环引用
    常用于 订阅者模式、事件系统、策略容器
*/
