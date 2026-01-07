#include "../exercise.h"
#include <cstring>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
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

    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    Tensor4D &operator+=(Tensor4D const &others) {
        for (unsigned int i = 0; i < shape[0]; ++i) {
            for (unsigned int j = 0; j < shape[1]; ++j) {
                for (unsigned int k = 0; k < shape[2]; ++k) {
                    for (unsigned int l = 0; l < shape[3]; ++l) {
                        unsigned int self_idx =
                            i * (shape[1] * shape[2] * shape[3]) +
                            j * (shape[2] * shape[3]) +
                            k * (shape[3]) +
                            l;

                        unsigned int o_i = (others.shape[0] == 1) ? 0 : i;
                        unsigned int o_j = (others.shape[1] == 1) ? 0 : j;
                        unsigned int o_k = (others.shape[2] == 1) ? 0 : k;
                        unsigned int o_l = (others.shape[3] == 1) ? 0 : l;

                        unsigned int others_idx =
                            o_i * (others.shape[1] * others.shape[2] * others.shape[3]) +
                            o_j * (others.shape[2] * others.shape[3]) +
                            o_k * (others.shape[3]) +
                            o_l;

                        data[self_idx] += others.data[others_idx];
                    }
                }
            }
        }
        return *this;
    }
};

// ---- 这里是缺失的 main 函数，确保它被包含在内 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        int data[]{
            1, 2, 3, 4,
            5, 6, 7, 8,
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
            1, 2, 3, 4,
            5, 6, 7, 8,
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
    return 0;
}