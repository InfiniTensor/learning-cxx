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

    // 直接对象调用
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);  // D没有重写virtual_name，使用C的实现
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    // 引用调用
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG);  // 虚函数，实际类型是B
    ASSERT(rbc.virtual_name() == 'C', MSG);  // 虚函数，实际类型是C
    ASSERT(rcd.virtual_name() == 'C', MSG);  // 虚函数，实际类型是D，使用C的实现
    ASSERT(rab.direct_name() == 'A', MSG);   // 普通函数，引用类型是A
    ASSERT(rbc.direct_name() == 'B', MSG);   // 普通函数，引用类型是B
    ASSERT(rcd.direct_name() == 'C', MSG);   // 普通函数，引用类型是C

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);  // 虚函数，实际类型是C
    ASSERT(rbd.virtual_name() == 'C', MSG);  // 虚函数，实际类型是D，使用C的实现
    ASSERT(rac.direct_name() == 'A', MSG);   // 普通函数，引用类型是A
    ASSERT(rbd.direct_name() == 'B', MSG);   // 普通函数，引用类型是B

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG);  // 虚函数，实际类型是D，使用C的实现
    ASSERT(rad.direct_name() == 'A', MSG);   // 普通函数，引用类型是A

    return 0;
}
