#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>
template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        // Copy shape and calculate total size
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
        }
        unsigned int size = shape[0] * shape[1] * shape[2] * shape[3];
        
        // Allocate memory and copy data
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // Delete copy and move constructors
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    Tensor4D &operator+=(Tensor4D const &others) {
        // Check if shapes are compatible for broadcasting
        for (int i = 0; i < 4; ++i) {
            if (shape[i] != others.shape[i] && others.shape[i] != 1) {
                // If shapes don't match and others' dimension isn't 1, broadcasting isn't possible
                throw std::runtime_error("Incompatible shapes for broadcasting");
            }
        }

        // Iterate through all elements of this tensor
        for (unsigned int i0 = 0; i0 < shape[0]; ++i0) {
            for (unsigned int i1 = 0; i1 < shape[1]; ++i1) {
                for (unsigned int i2 = 0; i2 < shape[2]; ++i2) {
                    for (unsigned int i3 = 0; i3 < shape[3]; ++i3) {
                        // Calculate index for this tensor
                        unsigned int idx = i0 * shape[1] * shape[2] * shape[3] +
                                        i1 * shape[2] * shape[3] +
                                        i2 * shape[3] +
                                        i3;
                        
                        // Calculate corresponding index for others tensor, using broadcasting
                        unsigned int o_idx = (i0 % others.shape[0]) * others.shape[1] * others.shape[2] * others.shape[3] +
                                           (i1 % others.shape[1]) * others.shape[2] * others.shape[3] +
                                           (i2 % others.shape[2]) * others.shape[3] +
                                           (i3 % others.shape[3]);
                        
                        // Add corresponding elements
                        data[idx] += others.data[o_idx];
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
