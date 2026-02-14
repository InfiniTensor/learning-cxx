#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    // 使用 inline static 在类内完成初始化
    // C++17 及以上版本支持 inline static 字段初始化
    inline static int num_a = 0;

    A() {
        ++num_a;
    }
    ///虚析构函数，确保通过基类指针删除派生类对象时，派生类的析构函数也会被调用
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};
struct B final : public A {
    // TODO: 正确初始化静态字段
    inline static int num_b = 0;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;

    }

    char name() const final {
        return 'B';
    }
};

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    // B 继承自 A，因此创建 B 对象时也会调用 A 的构造函数
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    // 1. 使用 dynamic_cast 进行安全的向下转换(推荐使用)（前提是基类有虚函数）
    // 2. 使用 static_cast 进行不安全的向下转换（速度快，但不安全）（
    // B &bb = *ab;
    B &bb = dynamic_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
