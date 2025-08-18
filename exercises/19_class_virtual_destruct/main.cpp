#include "../exercise.h"

struct A {
    // 静态成员在类内声明，类外初始化
    static int num_a;

    A() {
        ++num_a;
    }
    // 声明虚析构函数，确保派生类对象能正确析构
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

struct B final : public A {
    // 静态成员在类内声明，类外初始化
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

// 静态成员在类外初始化
int A::num_a = 0;
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    // new A: num_a=1; new B: 先构造A(num_a=2)，再构造B(num_b=1)
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;  // 派生类对象赋值给基类指针
    // new B: 先构造A(num_a=1)，再构造B(num_b=1)
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");  // 多态调用

    // 基类指针转换为派生类引用，使用static_cast（已知实际类型是B）
    B &bb = *static_cast<B*>(ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // 由于A有虚析构函数，delete会先调用B的析构函数，再调用A的析构函数
    delete ab;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
