#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>
/*
要求实现一个4D张量类模板 Tensor4D<T>，并实现带单向广播的加法 operator+=。重点是：
构造时计算 shape 总大小，拷贝数据；
加法时支持“单向广播”，即 others 的某些维度可能为1，对应维度的 this >1，会把 others 该维度数据重复广播加上去。
*/
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
        // 检查广播合法性
        for (int i = 0; i < 4; ++i) {
            ASSERT(others.shape[i] == 1 || shape[i] == others.shape[i],
                   "Broadcast shape mismatch");
        }
        // TODO: 实现单向广播的加法
        // 计算偏移时用的步长（C风格连续内存，最后维度变化最快）
        unsigned int this_strides[4], others_strides[4]; 
        this_strides[3] = 1; // 最后一维步长为1
        others_strides[3] = 1; // 最后一维步长为1
        for (int i = 2; i >= 0; --i) {
            this_strides[i] = this_strides[i + 1] * shape[i + 1]; // 计算每一维的步长
            others_strides[i] = others_strides[i + 1] * others.shape[i + 1]; // 计算每一维的步长
        }
        // 遍历所有元素的4D索引
        for (unsigned int i = 0; i < shape[0]; ++i) {
            for (unsigned int j = 0; j < shape[1]; ++j) {
                for (unsigned int k = 0; k < shape[2]; ++k) {
                    for (unsigned int l = 0; l < shape[3]; ++l) {
                        // 计算 this 和 others 的索引
                        unsigned int this_index = i * this_strides[0] + j * this_strides[1] +
                                                  k * this_strides[2] + l * this_strides[3]; // 计算 this 的索引
                        unsigned int others_index = (others.shape[0] == 1 ? 0 : i) * others_strides[0] +
                                                    (others.shape[1] == 1 ? 0 : j) * others_strides[1] +
                                                    (others.shape[2] == 1 ? 0 : k) * others_strides[2] +
                                                    (others.shape[3] == 1 ? 0 : l) * others_strides[3]; // 计算 others 的索引
                        data[this_index] += others.data[others_index]; // 执行加法
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
/*
这三个测试是为了验证：

    形状完全相同时的正常加法

    支持单向广播的加法（others中某些维度为1，对应维度较大时自动广播）

    标量广播（全1形状）

这是深度学习、数值计算中常用的“广播机制”，在交易系统（如多维数据张量、行情数据叠加等）中也非常实用。
*/
