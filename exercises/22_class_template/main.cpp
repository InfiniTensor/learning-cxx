#include "../exercise.h"
#include <cstring>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 复制输入形状到成员变量
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
        }
        // 计算总元素数量（4个维度的乘积）
        for (int i = 0; i < 4; ++i) {
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }
    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 补全单向广播加法逻辑
    Tensor4D &operator+=(Tensor4D const &others) {
        // 1. 检查广播合法性
        for (int i = 0; i < 4; ++i) {
            if (others.shape[i] != shape[i] && others.shape[i] != 1) {
                ASSERT(false, "Broadcast not supported: invalid dimension");
            }
        }

        // 2. 计算 this 的维度步长（4D索引转线性索引）
        unsigned int this_stride[4];
        this_stride[3] = 1;  // 最内层维度（第3维）步长为1
        this_stride[2] = shape[3] * this_stride[3];  // 第2维步长 = 第3维大小 × 第3维步长
        this_stride[1] = shape[2] * this_stride[2];  // 第1维步长 = 第2维大小 × 第2维步长
        this_stride[0] = shape[1] * this_stride[1];  // 第0维步长 = 第1维大小 × 第1维步长

        // 3. 计算 others 的维度步长
        unsigned int others_stride[4];
        others_stride[3] = 1;
        others_stride[2] = others.shape[3] * others_stride[3];
        others_stride[1] = others.shape[2] * others_stride[2];
        others_stride[0] = others.shape[1] * others_stride[1];

        // 4. 遍历 this 的所有元素，执行广播加法
        unsigned int total = shape[0] * shape[1] * shape[2] * shape[3];  // 总元素数
        for (unsigned int linear_idx = 0; linear_idx < total; ++linear_idx) {
            // 4.1 将 this 的线性索引转换为 4D 索引 (i0, i1, i2, i3)
            unsigned int i0 = linear_idx / this_stride[0];
            unsigned int rem0 = linear_idx % this_stride[0];  // 去除i0后的剩余偏移
            unsigned int i1 = rem0 / this_stride[1];
            unsigned int rem1 = rem0 % this_stride[1];  // 去除i1后的剩余偏移
            unsigned int i2 = rem1 / this_stride[2];
            unsigned int i3 = rem1 % this_stride[2];    // 第3维索引

            // 4.2 按广播规则映射 others 的 4D 索引 (o0, o1, o2, o3)
            // 若 others 维度为1，索引固定为0；否则与 this 索引一致
            unsigned int o0 = (others.shape[0] == 1) ? 0 : i0;
            unsigned int o1 = (others.shape[1] == 1) ? 0 : i1;
            unsigned int o2 = (others.shape[2] == 1) ? 0 : i2;
            unsigned int o3 = (others.shape[3] == 1) ? 0 : i3;

            // 4.3 将 others 的 4D 索引转换为线性索引
            unsigned int others_linear_idx = o0 * others_stride[0] + o1 * others_stride[1] +
                                             o2 * others_stride[2] + o3 * others_stride[3];

            // 4.4 执行元素级加法
            data[linear_idx] += others.data[others_linear_idx];
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