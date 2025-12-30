#include "../exercise.h"

// READ: 派生类 <https://zh.cppreference.com/w/cpp/language/derived_class>

static int i = 0;

struct X {
    int x;

    X(int x_) : x(x_) {
        std::cout << ++i << ". " << "X(" << x << ')' << std::endl;
    }
    X(X const &other) : x(other.x) {
        std::cout << ++i << ". " << "X(X const &) : x(" << x << ')' << std::endl;
    }
    ~X() {
        std::cout << ++i << ". " << "~X(" << x << ')' << std::endl;
    }
};
struct A {
    int a;

    A(int a_) : a(a_) {
        std::cout << ++i << ". " << "A(" << a << ')' << std::endl;
    }
    A(A const &other) : a(other.a) {
        std::cout << ++i << ". " << "A(A const &) : a(" << a << ')' << std::endl;
    }
    ~A() {
        std::cout << ++i << ". " << "~A(" << a << ')' << std::endl;
    }
};
struct B : public A {
    X x;

    B(int b) : A(1), x(b) { 
        std::cout << ++i << ". " << "B(" << a << ", X(" << x.x << "))" << std::endl;
    }
    B(B const &other) : A(other.a), x(other.x) {
        std::cout << ++i << ". " << "B(B const &) : A(" << a << "), x(X(" << x.x << "))" << std::endl;
    }
    ~B() {
        std::cout << ++i << ". " << "~B(" << a << ", X(" << x.x << "))" << std::endl;
    }
};

// 初始构造
int main(int argc, char **argv) {
    X x = X(1); // 调用X(int)
    A a = A(2); // 调用A(int)
    B b = B(3); // 调用B(int b)：调用A(1)，然后构造X(3)，然后打印B信息

    // TODO: 补全三个类型的大小
    static_assert(sizeof(X) == 4, "There is an int in X");
    static_assert(sizeof(A) == 4, "There is an int in A");
    static_assert(sizeof(B) == 8, "B is an A with an X");

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);

    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃的外层放进内层里。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    /*
    先构造一个完整的 B 对象：调用 B(int) 构造函数，先构造基类 A(1)，然后构造成员 X(5)，最后打印 B 构造信息。
    将 B 类型对象赋值给 A 类型对象 ab，发生对象切片：
    编译器允许从派生类对象 B 拷贝初始化基类对象 A，但只拷贝基类的那部分成员。
    ab 只存储了 A 部分的数据（即 a 变量的值），B 和 X 部分信息被丢弃。
    其实就是调用了 A 的拷贝构造函数，参数是 B 对象中的 A 子对象部分。
    打印输出 A(A const &) 信息，说明调用了基类的拷贝构造函数。
    原始的完整 B 临时对象会析构，调用 B 的析构函数，然后是 X 和 A 的析构函数。
    最后，ab 对象只剩下 A 部分，生命周期内只调用 A 的析构函数。
    */
    // THINK: 这样的代码是“安全”的吗？
    /*
    信息丢失：ab 只含有基类 A 部分，丢弃了 B 扩展的成员变量和状态。
    析构不对称：ab 是 A 类型对象，析构时只调用 A 的析构函数，B 的析构函数不会调用，可能导致派生类资源没释放。
    潜在语义错误：你可能误以为 ab 仍是一个完整的 B，但它不再具备 B 的特性和行为。
    不能访问派生类接口：例如 ab 无法调用 B 中新增的成员函数或访问成员变量。
    */
    // NOTICE: 真实场景中不太可能出现这样的代码
    /*
    这是对象切片（Object Slicing）！B(5) 创建了一个完整的 B 类型对象，但赋值给 A ab，只保留了它的 A 部分。
    也就是说，ab 是一个A 类型的对象，它来自一个 B 对象，但它不再拥有 B 的扩展内容（也不会调用 B 的析构函数）
    */
    /*
    安全性讨论
    这种代码虽然可以编译运行，但不建议使用，因为：
    会导致子类信息丢失（包括成员变量、虚函数等）
    析构函数不对称（会调用 A 的析构，而不是 B 的）
    真实项目中你很少这么写，除非刻意设计（例如拷贝基类接口）。
    */

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    return 0;
}
/*
对象切片是拷贝派生类对象给基类对象时的隐式行为，只保留基类数据。

这种写法合法，但一般不推荐，因为它会丢失派生类特性，容易导致逻辑错误。

真实代码中，应避免用值传递或赋值将派生类对象切片给基类对象，改用基类指针或引用以保持多态性。
*/