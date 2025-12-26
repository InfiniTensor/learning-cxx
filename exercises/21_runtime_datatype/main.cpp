#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

/// @brief 标签化联合体：通过type标记存储的是float还是double
struct TaggedUnion {
    DataType type;
    union {  // 匿名联合体，同一时间只能存储一个值
        float f;
        double d;
    };
};

// 函数模板：支持float和double类型的sigmoid计算
template <typename T>
T sigmoid(T x) {
    return 1 / (1 + std::exp(-x));
}

// 根据TaggedUnion的类型动态计算sigmoid
TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};  // 结果类型与输入类型一致
    switch (x.type) {
        case DataType::Float:
            ans.f = sigmoid(x.f);  // 处理float类型
            break;
        case DataType::Double:
            ans.d = sigmoid(x.d);  // 处理double类型
            break;
    }
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(yf.f == 1 / (1 + std::exp(-5.f)), "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(yd.d == 1 / (1 + std::exp(-5.0)), "sigmoid double");
    return 0;
}
