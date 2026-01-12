#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float, // 不赋值 默认0
    Double,// 默认递增
};

/// @brief Tagged union 即标签化联合体，是联合体的一种常见应用。
///        Rust enum 在实现上就是标签化联合体。
struct TaggedUnion {
    DataType type;
    // NOTICE: struct/union 可以相互任意嵌套。
    union { //此处的变量需要根据 type 进行取值
        float f;
        double d;
    };
};

// TODO: 将这个函数模板化用于 sigmoid_dyn
float sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}
double sigmoid(double x) {
    return 1 / (1 + std::exp(-x));
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    // TODO: 根据 type 调用 sigmoid
    if (ans.type == DataType::Float)
    {
        ans.f = sigmoid(x.f);
    } else if(ans.type == DataType::Double) {
        ans.d = sigmoid(x.d);
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
