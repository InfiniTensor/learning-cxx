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

int main(int argc, char **argv) {
    X x = X(1);
    A a = A(2);
    B b = B(3);

    // 补全三个类型的大小
    // X: 只有一个int成员，通常是4字节
    // A: 只有一个int成员，通常是4字节
    // B: 继承自A（包含一个int），又包含X（包含一个int），所以是两个int，通常是8字节
    // 注意：这里假设没有虚函数和虚表指针
    static_assert(sizeof(X) == sizeof(int), "There is an int in X");
    static_assert(sizeof(A) == sizeof(int), "There is an int in A");
    static_assert(sizeof(B) == 2 * sizeof(int), "B is an A with an X");

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);  // 错误：不能将基类转换为派生类

    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃的外层放进内层里。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    // THINK: 这样的代码是"安全"的吗？
    // NOTICE: 真实场景中不太可能出现这样的代码

    // 分析 A ab = B(5); 的执行步骤：
    // 1. 创建一个临时的 B 对象（调用 B 的构造函数）
    // 2. 用这个临时 B 对象的 A 部分（基类部分）来构造 ab（调用 A 的拷贝构造函数）
    // 3. 临时 B 对象被销毁（调用 B 的析构函数，再依次调用 ~X() 和 ~A()）
    // 4. main 函数结束时，ab 被销毁（调用 ~A()）

    // 这个过程会发生"对象切片"（Object Slicing）：派生类的额外信息被切掉，只保留基类部分

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 额外演示：通过指针或引用可以避免切片问题
    std::cout << "通过引用或指针避免切片：" << std::endl;
    B b2(6);
    A &a_ref = b2; // 通过引用，不会发生切片
    A *a_ptr = &b2;// 通过指针，不会发生切片

    // 但是注意：通过基类引用/指针只能访问基类的接口
    std::cout << "a_ref.a = " << a_ref.a << std::endl;

    return 0;
}