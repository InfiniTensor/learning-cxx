#include "../exercise.h"
#include <cmath>

enum class DataType { Float, Double };

struct TaggedUnion {
    DataType type;
    union { float f; double d; };
};

// 模板化 sigmoid
template <typename T>
T sigmoid(T x) { return T(1) / (T(1) + std::exp(-x)); }

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    switch (x.type) {
        case DataType::Float:  ans.f = sigmoid(x.f); break;
        case DataType::Double: ans.d = sigmoid(x.d); break;
    }
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int, char**) {
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