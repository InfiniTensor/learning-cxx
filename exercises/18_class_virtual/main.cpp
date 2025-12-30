#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>
/*
在低延迟交易系统中，这种行为至关重要：
✅ 虚函数的利：
    提供了灵活的多态性，便于构建策略类、风控接口、订单工厂等组件。

❌ 虚函数的弊：
    每次调用要查 vtable（虚函数表），多一个间接跳转指令，可能会：
        破坏 CPU 分支预测
        增加指令流水中的延迟（尤其对 L1 cache 敏感的撮合系统）
因此：
    延迟敏感的系统往往只在必要的地方使用 virtual，甚至使用 final 和 noexcept 优化虚函数调用。
*/
struct A {
    virtual char virtual_name() const { // virtual_name()是虚函数，虚函数支持运行时多态，也就是说函数调用是在运行时动态解析的
        return 'A';
    }
    char direct_name() const {  // direct_name()是非虚函数，非虚函数是静态绑定，也就是编译器就决定了调用哪个函数。
        // 如果用对象调用（而非指针/引用），就调用当前类型的函数版本
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override { // override关键字能让编译器帮你检查是否真的重写了基类的虚函数
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {  // final 修饰符表示这个虚函数不能被进一步重写，编译器因此可以在某些场景下优化虚表查找
        // 对于性能敏感的系统（如HFT交易系统），可以减少运行时开销
        // 这是这个虚函数链的最终实现，不能再被override。编译器可以进行devirtualization优化：
        // 假设调用不会再变成别的子类版本，可以直接内联；提升性能
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
    ASSERT(d.virtual_name() == 'C', MSG); // 调用 C::virtual_name()，因为 D 没有 override 它。virtual：找最近的override -> C
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG); // 调用 D::direct_name()，因为 D 自己定义了。非virtual：静态绑定 -> D

    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); // A& -> B 实例 => B::virtual_name()
    ASSERT(rbc.virtual_name() == 'C', MSG); // B& -> C 实例 => C::virtual_name()
    ASSERT(rcd.virtual_name() == 'C', MSG); // C& -> D 实例 => C::virtual_name() 是 final，不可 override

    ASSERT(rab.direct_name() == 'A', MSG);  // 静态类型 A => A::direct_name()
    ASSERT(rbc.direct_name() == 'B', MSG);  // 静态类型 B => B::direct_name()
    ASSERT(rcd.direct_name() == 'C', MSG);  // 静态类型 C => C::direct_name()

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // C 实例 => C::virtual_name()
    ASSERT(rbd.virtual_name() == 'C', MSG); // D 实例 => C::virtual_name()（final，无法 override）
    ASSERT(rac.direct_name() == 'A', MSG); // 静态类型 A => A::direct_name()
    ASSERT(rbd.direct_name() == 'B', MSG); // 静态类型 B => B::direct_name()

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // D 实例 => C::virtual_name()（final）
    ASSERT(rad.direct_name() == 'A', MSG);  // 静态类型 A => A::direct_name()

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
