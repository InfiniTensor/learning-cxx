#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10); // 整数10被创建一个共享指针
    std::shared_ptr<int> ptrs[]{shared, shared, shared};
    // std::cout<<shared.use_count()<<std::endl; // 4
    std::weak_ptr<int> observer = shared; // 不影响引用
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset(); // 引用计数减1
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr; //引用计数减1
    ASSERT(observer.use_count() == 2, "");

    
    ptrs[2] = std::make_shared<int>(*shared); //相当于重新创建一个对象 引用计数减1

    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared; // 引用计数加1
    ptrs[1] = shared; //引用计数加1
    ptrs[2] = std::move(shared);  // 右值,引用计数不变
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]); // 取 ptrs[0] 的右值然后释放,引用计数不变
    ptrs[1] = std::move(ptrs[1]); // 引用计数不变
    ptrs[1] = std::move(ptrs[2]); // 引用计数减1
    std::cout<<observer.use_count()<<std::endl;
    ASSERT(observer.use_count() == 2, ""); //ptrs[2] 还在 shared 还在

    shared = observer.lock(); // 这步没看懂
    std::cout<<observer.use_count()<<std::endl;
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}

/*
    a[0].reset()
    a[0] 放弃对 MyClass(0) 对象的所有权

    对象的引用计数从 1 减为 0

    引用计数为 0，触发对象销毁

    MyClass(0) 的析构函数被调用

    a[0] 变为空指针（nullptr）
*/

/*
std::ignore = std::move(ptrs[0]); 这行代码的意思通常是：

    std::move(ptrs[0])：将 ptrs[0] 转换为右值引用，准备移动

    std::ignore = ...：将移动后的结果赋值给 std::ignore，实际上就是丢弃这个值

这相当于显式地 "销毁" 或 "释放" ptrs[0] 所管理的资源。

*/


/*
这行代码实际上发生了多个步骤：
步骤1：observer.lock()

    尝试创建一个新的 shared_ptr 指向被观察的对象

    因为对象还存在（引用计数>0），所以成功

    创建一个临时的 shared_ptr

    引用计数从 1 增加到 2

步骤2：赋值操作 shared = ...

    将 shared 原来指向的对象引用计数减 1（从2减到1）

    然后 shared 指向新创建的临时 shared_ptr 的对象（同一个对象）

    引用计数从 1 增加到 2

步骤3：临时对象销毁

    临时 shared_ptr 销毁，引用计数从 2 减到 1

最终状态：

    引用计数：1
*/