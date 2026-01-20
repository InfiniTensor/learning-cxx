#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// std::shared_ptr 实现的是共享所有权，多个指针可以同时指向一个对象，创建一个shared_ptr时，系统会在堆上创建一个控制块，计数有多少个shared_ptr（强引用计数）和weak_ptr（弱引用计数）指向该对象
// std::weak_ptr指向对象但不拥有对象，它的use_count返回的是指向该对象的shared_ptr数量

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};    // 拷贝了3次

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);   // 这一步相当于创建了一个新的对象，让ptrs[2]指向新对象，2个对象虽然值一样，但是地址不一样，是2个东西
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);    // 移动语义，把shared掏空，3个是ptrs[0], ptrs[1], ptrs[2]
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);   // std::ignore一般用来占位并忽略掉不需要的值，但其实没有执行完一行代码自己销毁的机制，可以理解为只是叫这个名字，所以这里的observer.use_count()不要-1
    ASSERT(observer.use_count() == 3, "");
    ptrs[1] = std::move(ptrs[1]);
    ASSERT(observer.use_count() == 3, "");
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();   // lock将weak_ptr提升为shared_ptr，shared像胡汉三一样又回来了，然后lock的函数签名里有const，不改变observer本身还是weak_ptr，所以计数要+1
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    // 这个for循环跟Python写法for ptr in ptrs一样的逻辑，Python的for循环也是引用，会改变源变量的值，C++要指定清楚是引用还是值传递
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
