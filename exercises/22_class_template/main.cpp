#include "../exercise.h"
#include <cstring>
#include <algorithm>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        // 拷贝 shape 并计算总元素个数
        std::copy(shape_, shape_ + 4, shape);
        unsigned int size = shape[0] * shape[1] * shape[2] * shape[3];
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() { delete[] data; }

    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    /* 单向广播加法：
       others 维度长度要么与 *this 相同，要么为 1。
       长度为 1 的维度在计算时重复其唯一元素。
    */
    Tensor4D &operator+=(Tensor4D const &others) {
        auto idx = [this](unsigned int n, unsigned int c,
                          unsigned int h, unsigned int w) {
            return ((n * shape[1] + c) * shape[2] + h) * shape[3] + w;
        };
        auto o_idx = [&others](unsigned int n, unsigned int c,
                               unsigned int h, unsigned int w) {
            return ((n * others.shape[1] + c) * others.shape[2] + h)
                   * others.shape[3] + w;
        };

        for (unsigned int n = 0; n < shape[0]; ++n) {
            unsigned int on = std::min(n, others.shape[0] - 1);
            for (unsigned int c = 0; c < shape[1]; ++c) {
                unsigned int oc = std::min(c, others.shape[1] - 1);
                for (unsigned int h = 0; h < shape[2]; ++h) {
                    unsigned int oh = std::min(h, others.shape[2] - 1);
                    for (unsigned int w = 0; w < shape[3]; ++w) {
                        unsigned int ow = std::min(w, others.shape[3] - 1);
                        data[idx(n, c, h, w)] +=
                            others.data[o_idx(on, oc, oh, ow)];
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
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,
            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        unsigned int s1[]{1, 2, 3, 1};
        float d1[]{6, 5, 4, 3, 2, 1};
        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
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