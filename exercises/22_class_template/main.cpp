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
        for (int i = 0; i < 4; i++) {
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
        // 步骤1：校验广播合法性（单向广播规则）
        for (int d = 0; d < 4; ++d) {
            ASSERT(
                others.shape[d] == this->shape[d] || others.shape[d] == 1,
                "Broadcast error: others shape[%d] must be 1 or equal to this shape[%d]"
            );
        }

        // 步骤2：计算this的维度步长（stride）——用于线性索引转4维坐标
        unsigned int this_stride[4];
        this_stride[3] = 1;                    // d3的步长：每个d3元素占1个位置
        this_stride[2] = this->shape[3] * this_stride[3];  // d2的步长：d2* d3总数
        this_stride[1] = this->shape[2] * this_stride[2];  // d1的步长：d1* d2*d3总数
        this_stride[0] = this->shape[1] * this_stride[1];  // d0的步长：d0* d1*d2*d3总数
        unsigned int this_size = this->shape[0] * this_stride[0];  // this总元素数

        // 步骤3：计算others的维度步长（用于4维坐标转线性索引）
        unsigned int others_stride[4];
        others_stride[3] = 1;
        others_stride[2] = others.shape[3] * others_stride[3];
        others_stride[1] = others.shape[2] * others_stride[2];
        others_stride[0] = others.shape[1] * others_stride[1];

        // 步骤4：遍历每个元素，执行广播加法
        for (unsigned int i = 0; i < this_size; ++i) {
            // 4.1 把this的线性索引i转换为4维坐标 (d0, d1, d2, d3)
            unsigned int d0 = (i / this_stride[0]) % this->shape[0];
            unsigned int d1 = (i / this_stride[1]) % this->shape[1];
            unsigned int d2 = (i / this_stride[2]) % this->shape[2];
            unsigned int d3 = (i / this_stride[3]) % this->shape[3];

            // 4.2 计算others的对应4维坐标（广播维度取0）
            unsigned int o_d0 = (others.shape[0] == 1) ? 0 : d0;
            unsigned int o_d1 = (others.shape[1] == 1) ? 0 : d1;
            unsigned int o_d2 = (others.shape[2] == 1) ? 0 : d2;
            unsigned int o_d3 = (others.shape[3] == 1) ? 0 : d3;

            // 4.3 把others的4维坐标转换为线性索引j
            unsigned int j = o_d0 * others_stride[0] + 
                             o_d1 * others_stride[1] + 
                             o_d2 * others_stride[2] + 
                             o_d3 * others_stride[3];

            // 4.4 执行广播加法
            this->data[i] += others.data[j];
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
