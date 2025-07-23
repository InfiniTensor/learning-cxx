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
    /**
    广播加法实现：
        形状检查：确保 others 的每个维度要么与 this 相同，要么为 1（允许广播）。
        步长计算：计算每个维度的步长（stride），用于快速索引元素。
        四维循环：遍历 this 的每个元素，根据广播规则计算 others 中对应的元素索引。
        索引映射：当 others 的某个维度为 1 时，该维度的索引固定为 0（实现广播）。

    广播机制示例:
        示例 1：this 形状 [1,2,3,4]，others 形状 [1,2,1,4]
            第三维：others.shape[2] == 1，因此 others 在该维度上的索引始终为 0，实现对 this 第三维的每个元素广播。
        示例 2：others 形状 [1,1,1,1]
            所有维度均为 1，others 的单个元素会广播到 this 的所有元素。
    */
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法

        // Step 1: Shape Check
        for (int i = 0; i < 4; ++i) {
            if (others.shape[i] != shape[i] && others.shape[i] != 1) {
                throw std::invalid_argument("Tensor shapes are incompatible for broadcasting");
            }
        }

        // Step 2: Calculate strides
        unsigned int this_strides[4] = {
            shape[1] * shape[2] * shape[3],
            shape[2] * shape[3],
            shape[3],
            1};
        unsigned int other_strides[4] = {
            others.shape[1] * others.shape[2] * others.shape[3],
            others.shape[2] * others.shape[3],
            others.shape[3],
            1};

        // Step 3: Calculate with strides
        for (unsigned int i0 = 0; i0 < shape[0]; ++i0) {
            for (unsigned int i1 = 0; i1 < shape[1]; ++i1) {
                for (unsigned int i2 = 0; i2 < shape[2]; ++i2) {
                    for (unsigned int i3 = 0; i3 < shape[3]; ++i3) {
                        // Step 3.1: Calculate this's stride
                        unsigned int this_idx = i0 * this_strides[0] + i1 * this_strides[1] + i2 * this_strides[2] + i3 * this_strides[3];

                        // Step 3.2: Calculate other's stride
                        // 对于others，当维度为1时使用0作为索引（广播）
                        unsigned int other_i0 = (others.shape[0] == 1) ? 0 : i0;
                        unsigned int other_i1 = (others.shape[1] == 1) ? 0 : i1;
                        unsigned int other_i2 = (others.shape[2] == 1) ? 0 : i2;
                        unsigned int other_i3 = (others.shape[3] == 1) ? 0 : i3;
                        unsigned int other_idx = other_i0 * other_strides[0] + other_i1 * other_strides[1] + other_i2 * other_strides[2] + other_i3 * other_strides[3];

                        // Step 3.3: 执行加法
                        data[this_idx] += others.data[other_idx];
                    }
                }
            }
        }

        return *this;
    }
};

// 推导指引，帮助编译器从构造函数参数推导模板参数 T
// For < cxx17
template<class T>
Tensor4D(const unsigned int[4], T const*) -> Tensor4D<T>;

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
