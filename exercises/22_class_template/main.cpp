#include "../exercise.h"
#include <cstring>

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template <class T>
struct Tensor4D {
    unsigned int shape[4]{};
    T *data = nullptr;

    // 用指针形式更好匹配：unsigned int const shape_[4] 在参数处也会退化成指针
    Tensor4D(const unsigned int *shape_, const T *data_) {
        unsigned int size = 1;

        // 1) 复制 shape 并计算 size（四个维度相乘）
        for (int d = 0; d < 4; ++d) {
            shape[d] = shape_[d];
            size *= shape[d];
        }

        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() { delete[] data; }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 单向广播加法：others 的每一维要么等于 this，要么为 1
    Tensor4D &operator+=(Tensor4D const &others) {
        // 2) 形状检查：不满足就直接断言失败
        for (int d = 0; d < 4; ++d) {
            ASSERT(others.shape[d] == shape[d] || others.shape[d] == 1,
                   "Invalid broadcast shape");
        }

        // 3) 遍历 this 的所有坐标 (i0,i1,i2,i3)
        //    others 对应坐标 (o0,o1,o2,o3)：如果 others 该维是 1，则该维永远取 0（广播）
        for (unsigned int i0 = 0; i0 < shape[0]; ++i0) {
            unsigned int o0 = (others.shape[0] == 1 ? 0 : i0);
            for (unsigned int i1 = 0; i1 < shape[1]; ++i1) {
                unsigned int o1 = (others.shape[1] == 1 ? 0 : i1);
                for (unsigned int i2 = 0; i2 < shape[2]; ++i2) {
                    unsigned int o2 = (others.shape[2] == 1 ? 0 : i2);
                    for (unsigned int i3 = 0; i3 < shape[3]; ++i3) {
                        unsigned int o3 = (others.shape[3] == 1 ? 0 : i3);

                        // this 的一维下标（按行主序展平）
                        unsigned int idx =
                            ((i0 * shape[1] + i1) * shape[2] + i2) * shape[3] + i3;

                        // others 的一维下标（同样展平，但用广播后的 o0..o3）
                        unsigned int oidx =
                            ((o0 * others.shape[1] + o1) * others.shape[2] + o2) *
                                others.shape[3] +
                            o3;

                        data[idx] += others.data[oidx];
                    }
                }
            }
        }
        return *this;
    }
};

// ✅ 类模板参数推导指引（让 auto t0 = Tensor4D(shape, data) 能推导出 T）
template <class T>
Tensor4D(const unsigned int *, const T *) -> Tensor4D<T>;

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
