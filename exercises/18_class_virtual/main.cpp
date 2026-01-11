#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

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
    // 注意：virtual_name() 在 C 中被声明为 final
    // 所以 D 不能重写 virtual_name()
    // 如果尝试重写，会编译错误
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 测试对象直接调用
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);// D 没有重写 virtual_name，使用 C 的实现

    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    // 测试通过基类引用调用
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    // 虚函数：动态绑定，取决于实际对象类型
    ASSERT(rab.virtual_name() == 'B', MSG);
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG);

    // 非虚函数：静态绑定，取决于引用类型
    ASSERT(rab.direct_name() == 'A', MSG);// 静态类型是 A，调用 A::direct_name()
    ASSERT(rbc.direct_name() == 'B', MSG);// 静态类型是 B，调用 B::direct_name()
    ASSERT(rcd.direct_name() == 'C', MSG);// 静态类型是 C，调用 C::direct_name()

    // 测试多层继承的引用
    A &rac = c;
    B &rbd = d;

    // 虚函数：动态绑定
    ASSERT(rac.virtual_name() == 'C', MSG);
    ASSERT(rbd.virtual_name() == 'C', MSG);// D 没有重写，使用 C 的实现

    // 非虚函数：静态绑定
    ASSERT(rac.direct_name() == 'A', MSG);// 静态类型是 A
    ASSERT(rbd.direct_name() == 'B', MSG);// 静态类型是 B

    // 测试最顶层的引用
    A &rad = d;

    // 虚函数：动态绑定，实际对象是 D，但 D 没有重写，使用 C 的实现
    ASSERT(rad.virtual_name() == 'C', MSG);

    // 非虚函数：静态绑定
    ASSERT(rad.direct_name() == 'A', MSG);// 静态类型是 A

    // 打印验证结果
    std::cout << "所有断言通过！" << std::endl;
    std::cout << "虚函数展示多态性：" << std::endl;
    std::cout << "A& ref_to_b 调用 virtual_name(): " << rab.virtual_name() << std::endl;
    std::cout << "A& ref_to_b 调用 direct_name(): " << rab.direct_name() << std::endl;

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>