#include "../exercise.h"
#include <cstring>
#include <stdexcept>// 添加stdexcept头文件用于异常处理

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
            size *= shape_[i];
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

    // 这个加法需要支持"单向广播"。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为 1。
    // `others` 长度为 1 但 `this` 长度不为 1 的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3 个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法
        // 检查形状是否兼容
        for (int i = 0; i < 4; i++) {
            if (shape[i] != others.shape[i] && others.shape[i] != 1) {
                throw std::runtime_error("Incompatible shapes for broadcasting");
            }
        }

        // 计算每个维度的步长（stride）
        unsigned int stride[4];
        stride[3] = 1;// 最后一个维度步长为1
        stride[2] = shape[3];
        stride[1] = shape[2] * shape[3];
        stride[0] = shape[1] * shape[2] * shape[3];

        unsigned int other_stride[4];
        other_stride[3] = 1;// 最后一个维度步长为1
        other_stride[2] = others.shape[3];
        other_stride[1] = others.shape[2] * others.shape[3];
        other_stride[0] = others.shape[1] * others.shape[2] * others.shape[3];

        // 遍历所有元素
        for (unsigned int i = 0; i < shape[0]; i++) {
            for (unsigned int j = 0; j < shape[1]; j++) {
                for (unsigned int k = 0; k < shape[2]; k++) {
                    for (unsigned int l = 0; l < shape[3]; l++) {
                        // 计算当前元素在this中的索引
                        unsigned int index = i * stride[0] + j * stride[1] + k * stride[2] + l * stride[3];

                        // 计算对应元素在others中的索引（考虑广播）
                        unsigned int i_other = (others.shape[0] == 1) ? 0 : i;
                        unsigned int j_other = (others.shape[1] == 1) ? 0 : j;
                        unsigned int k_other = (others.shape[2] == 1) ? 0 : k;
                        unsigned int l_other = (others.shape[3] == 1) ? 0 : l;

                        unsigned int other_index = i_other * other_stride[0] +
                                                   j_other * other_stride[1] +
                                                   k_other * other_stride[2] +
                                                   l_other * other_stride[3];

                        // 执行加法
                        data[index] += others.data[other_index];
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
    return 0;
}