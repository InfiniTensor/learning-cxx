#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>
// 虚函数（Virtual Function） 是实现多态（Polymorphism）的核心机制。
// - 它允许你在派生类（子类）中重写基类（父类）定义的函数
// - 并确保通过基类指针或引用调用该函数时，实际执行的是子类中的版本。
// <---->
// 虚函数：
// - 在基类中使用关键字 virtual 声明的函数称为虚函数。
// - 在派生类使用override 关键字用于明确表示重写
// class Base {
// public:
//     virtual void show() {
//         cout << "这是基类的 show 函数" << endl;
//     }
// };
// class Derived : public Base {
// public:
//     void show() override { // override 关键字用于明确表示重写（C++11）
//         cout << "这是派生类的 show 函数" << endl;
//     }
// };
// <---->
// final 关键字有两个主要用途：禁止虚函数被进一步重写 以及 禁止类被继承。
// - 当在派生类中将一个虚函数标记为 final 时，任何尝试在更深层的子类中重写该函数的行为都会导致编译错误。
// - 如果将 final 放在类名后面，则表示该类是“最终类”，不允许任何类继承它。

// 核心口诀：
// - 虚函数看对象（实际是谁就调谁）。
// - 普通函数看类型（声明是谁就调谁）。
// - final 锁死子类（不影响父类引用调自己）。
struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
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

    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG);
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG);
    ASSERT(rab.direct_name() == 'A', MSG);
    ASSERT(rbc.direct_name() == 'B', MSG);
    ASSERT(rcd.direct_name() == 'C', MSG);

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);
    ASSERT(rbd.virtual_name() == 'C', MSG);
    ASSERT(rac.direct_name() == 'A', MSG);
    ASSERT(rbd.direct_name() == 'B', MSG);

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG);
    ASSERT(rad.direct_name() == 'A', MSG);

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
