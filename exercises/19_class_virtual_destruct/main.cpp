#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    // static int num_a = 0; 错误：不能在类定义中直接赋值/初始化（除非是 constexpr 或 inline）
    /*
    inline 是编译器优化的一种方式：inline int add(int a, int b) { return a + b; }
    调用 add(1, 2) 会直接替换为 1 + 2，避免函数调用开销（如压栈/跳转/返回）。
    对低延迟系统（如交易撮合）很重要，因为每次函数调用的成本可能影响微秒级性能。
    */

    static int num_a; // 声明（类内）
  
    A() {
        ++num_a; 
    }
    
    /*
    ~A() {
        --num_a; 这里 A 的析构函数不是虚析构。导致通过 A* ab = new B; 删除时，只会调用 A 的析构函数，B 的析构函数没调用，B::num_b 不减，造成计数不对。
    }
    */
    // 将A的析构函数声明为虚析构函数，确保通过基类指针删除派生类对象时，派生类的析构函数也会被调用。
    virtual ~A() {
        --num_a; // 虚析构函数：确保派生类对象被删除时，基类的析构函数也会被调用
    }// 这样删除派生类对象时，才能正确调用B的析构函数，更新B::num_b。

    virtual char name() const {
        return 'A';
    }
};
struct B final : public A {
    // TODO: 正确初始化静态字段
    // static int num_b = 0;
    static int num_b; // 声明（类内）

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
// 类定义后，初始化静态成员变量
int A::num_a = 0; // 定义（类外）
int B::num_b = 0; // 定义（类外）

int main(int argc, char **argv) {
    auto a = new A; // A构造：num_a++
    auto b = new B; // B构造：num_b++
    
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    // 删除对象
    delete a; // A析构：num_a--
    delete b; // B析构：num_b--
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    // 多态指针
    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()"); // 虚函数

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    // 向下转型
    // B &bb = *ab; // ab 实际指向的是 B 类型对象，安全地强转为 B&。编译器报错，因为缺少强制类型转换或者ab指针类型为基类指针，需要用static_cast或dynamic_cast
    B &bb = static_cast<B&>(*ab); // 把基类引用强转为派生类引用
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()"); 

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
