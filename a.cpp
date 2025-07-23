#include <iostream>
#include <type_traits> // 用于检查类型
#include <bits/stdc++.h> // 包含所有标准库头文件

// 这是一个简单的帮助函数，用来告诉你一个值是左值还是右值
void print_value_category(int& val) {
    std::cout << "  -> 接收到一个【左值引用】" << std::endl;
}

void print_value_category(int&& val) {
    std::cout << "  -> 接收到一个【右值引用】" << std::endl;
}

// 我们的模板函数，使用了 T&& 形参
template <typename T>
void inspect_param(T&& param) {
    std::cout << "  在 inspect_param 内部，参数 param 的类型是: ";
    // 注意：decltype(param) 会告诉你 param 变量本身的类型
    // std::is_lvalue_reference 和 std::is_rvalue_reference 可以确认其引用类型
    if (std::is_lvalue_reference<decltype(param)>::value) {
        std::cout << "左值引用 (T&)";
    } else if (std::is_rvalue_reference<decltype(param)>::value) {
        std::cout << "右值引用 (T&&)";
    } else {
        std::cout << "值类型";
    }
    std::cout << "。\n";

    // param 虽然类型可能是右值引用，但因为它有了名字，在函数内部它本身是【左值】
    std::cout << "  现在把 param 传给 print_value_category：";
    print_value_category(param); // 注意这里：直接传 param 总是传左值！
}

void example_reference_collapsing() {
    std::cout << "--- 场景一：传入一个【右值】(字面量 10) ---" << std::endl;
    inspect_param(10); // 传入一个右值字面量

    std::cout << "\n--- 场景二：传入一个【左值】(变量 num) ---" << std::endl;
    int num = 20; // num 是一个左值
    inspect_param(num); // 传入一个左值变量
}

/*
运行 example_reference_collapsing() 的输出会是这样：

--- 场景一：传入一个【右值】(字面量 10) ---
  在 inspect_param 内部，参数 param 的类型是: 右值引用 (T&&)。
  现在把 param 传给 print_value_category：  -> 接收到一个【左值引用】

--- 场景二：传入一个【左值】(变量 num) ---
  在 inspect_param 内部，参数 param 的类型是: 左值引用 (T&)。
  现在把 param 传给 print_value_category：  -> 接收到一个【左值引用】
*/