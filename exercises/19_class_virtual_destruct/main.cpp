#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态字段在类内声明
    static int num_a;

    A() {
        ++num_a;
    }
    // TODO: 必须是虚析构函数，否则通过 A* 删除 B 对象时，~B() 不会被调用
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 在类外初始化静态字段
int A::num_a = 0;

struct B final : public A {
    static int num_b;

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

// 在类外初始化静态字段
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    // B 继承自 A，所以创建 B 时也会调用 A 的构造函数
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 使用 dynamic_cast 进行安全的向下转换
    B &bb = dynamic_cast<B &>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // 如果 ~A() 不是 virtual，delete ab 只会调用 ~A()，导致 num_b 保持为 1
    delete ab;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}