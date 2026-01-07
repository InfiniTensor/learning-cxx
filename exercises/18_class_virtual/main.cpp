#include "../exercise.h"

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    // D 没有重写 virtual_name，将使用 C 的实现
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 直接对象调用：直接调用该类的成员
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);// D 继承了 C 的虚函数
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    // 引用调用：
    // virtual_name 表现为多态（看对象实际是谁）
    // direct_name  表现为静态绑定（看引用的类型是谁）
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG);// 实际对象是 B
    ASSERT(rbc.virtual_name() == 'C', MSG);// 实际对象是 C
    ASSERT(rcd.virtual_name() == 'C', MSG);// 实际对象是 D，但 D 用的 C 的虚函数
    ASSERT(rab.direct_name() == 'A', MSG); // 引用类型是 A
    ASSERT(rbc.direct_name() == 'B', MSG); // 引用类型是 B
    ASSERT(rcd.direct_name() == 'C', MSG); // 引用类型是 C

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);// 实际对象是 C
    ASSERT(rbd.virtual_name() == 'C', MSG);// 实际对象是 D，其虚函数来自 C
    ASSERT(rac.direct_name() == 'A', MSG); // 引用类型是 A
    ASSERT(rbd.direct_name() == 'B', MSG); // 引用类型是 B

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG);// 实际对象是 D，其虚函数来自 C
    ASSERT(rad.direct_name() == 'A', MSG); // 引用类型是 A

    return 0;
}