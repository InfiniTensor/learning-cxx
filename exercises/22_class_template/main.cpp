#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为 1。
    // `others` 长度为 1 但 `this` 长度不为 1 的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3 个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法

        // 1. 计算 others 在各个维度上的“有效步长”
        // 如果 others.shape[i] == 1，说明该维度需要广播，
        // 意味着无论目标索引在这个维度怎么变，others 取值都应该取第 0 个，
        // 所以步长设为 0。否则步长为正常的累乘值。

        // 维度 3 (最内层)
        unsigned int s3 = (others.shape[3] == 1) ? 0 : 1;
        // 维度 2
        unsigned int s2 = (others.shape[2] == 1) ? 0 : others.shape[3];
        // 维度 1
        unsigned int s1 = (others.shape[1] == 1) ? 0 : others.shape[2] * others.shape[3];
        // 维度 0 (最外层)
        unsigned int s0 = (others.shape[0] == 1) ? 0 : others.shape[1] * others.shape[2] * others.shape[3];

        T *dst = data;       // 指向 this 的数据头
        T *src = others.data;// 指向 others 的数据头

        // 2. 遍历 this 的每一个元素
        for (unsigned int n = 0; n < shape[0]; ++n) {
            for (unsigned int c = 0; c < shape[1]; ++c) {
                for (unsigned int h = 0; h < shape[2]; ++h) {
                    for (unsigned int w = 0; w < shape[3]; ++w) {
                        // 3. 计算 others 对应的偏移量
                        // 也就是: n*stride0 + c*stride1 + h*stride2 + w*stride3
                        // 因为广播维度的 stride 是 0，所以自动实现了“坐标归零”的效果
                        unsigned int src_offset = n * s0 + c * s1 + h * s2 + w * s3;

                        // 4. 加法运算
                        *dst += src[src_offset];

                        // 5. dst 指针自增（因为我们是按顺序遍历的）
                        ++dst;
                    }
                }
            }
        }
        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
