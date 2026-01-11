#include "../exercise.h"
#include <cassert>// 添加 assert 头文件

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态字段需要在类外定义和初始化
    static int num_a;

    A() {
        ++num_a;
    }

    // 需要将析构函数声明为虚函数，以便通过基类指针正确删除派生类对象
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 在类外定义和初始化静态成员
int A::num_a = 0;

struct B final : public A {
    // 静态字段需要在类外定义和初始化
    static int num_b;

    B() {
        ++num_b;
    }

    ~B() override {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

// 在类外定义和初始化静态成员
int B::num_b = 0;

int main(int argc, char **argv) {
    // 测试基本创建和删除
    auto a = new A;
    auto b = new B;

    // A::num_a = 2 (1个A + 1个B中的A部分)
    // B::num_b = 1 (1个B)
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    // 测试多态删除
    A *ab = new B;                                                        // 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");      // B对象包含A部分
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");      // B对象本身
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");// 多态调用

    // 基类指针转换为派生类引用，使用dynamic_cast进行安全的向下转型
    // 因为B是final，所以可以使用static_cast，但dynamic_cast更安全
    B &bb = dynamic_cast<B &>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象

    // 需要虚析构函数才能正确调用派生类的析构函数
    // 如果没有虚析构函数，只会调用基类的析构函数
    // B对象的B部分不会被正确销毁，B::num_b不会减少

    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}