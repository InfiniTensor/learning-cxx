#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

// 左值 (Lvalue) vs 右值 (Rvalue):
//    - 左值：有名字、有固定地址的对象（如变量名 fib）。可以取址&。
//    - 右值：临时的、即将销毁的对象（如 std::move(fib) 的返回值，或临时计算结果）。不能取址&。
//    - 右值引用（Rvalue Reference） 是 C++11 引入的一种新引用类型，专门用来绑定到临时对象（右值）上。
// 移动语义 (Move Semantics):
//    - 核心在于“接管”资源而非“复制”资源。对于动态分配的内存，移动只需交换指针。
//    - 核心思想：“剪切 + 粘贴” 而不是 “复制 + 粘贴”。
// 换言之，移动语义意味着“接管”资源而非“复制”资源。
// noexcept:
//    - 移动构造和移动赋值通常标记为 noexcept，告知编译器此操作不会抛出异常，
//      这对于 std::vector 等容器在扩容时的性能优化至关重要。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {
        if (capacity>0) cache[0] = 0;
        if (capacity>1) cache[1] = 1;
    }

    // TODO: 实现移动构造器
    // 通过右值引用(&&),接管 other 的资源，将other置于有效但未定义状态(指针置空)
    DynFibonacci(DynFibonacci && other) noexcept : cache(other.cache), cached(other.cached) {
        // 断开对原对象的内存引用
        other.cache = nullptr;
        other.cached = 0;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    // 移动赋值需要先释放自己的资源，再接管别人的资源
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        //自赋值检查，防止fib=std::move(fib)导致资源提取释放
        if(this!= &other){
            //1.释放旧资源
            delete[] cache;
            //2.接管新资源
            cache = other.cache;
            cached = other.cached;
            //3.断开对原对象的内存引用
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
