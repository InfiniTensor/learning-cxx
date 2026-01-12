#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) { // 构造函数
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for (int i = 0; i < 4; i++)
        {
            shape[i] = shape_[i];
        }
        
        size = size * shape_[0] * shape_[1]* shape_[2]* shape_[3];
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
    // 辅助函数：计算元素的线性索引
    unsigned int get_linear_index(unsigned int i0, unsigned int i1, 
                                  unsigned int i2, unsigned int i3) const {
        return ((i0 * shape[1] + i1) * shape[2] + i2) * shape[3] + i3;
    }
    Tensor4D &operator+=(Tensor4D const &other) {
        // TODO: 实现单向广播的加法
        for (int i = 0; i < 4; i++) {
            // 对于每个维度，要么长度相等，要么other的长度为1
            if (!(shape[i] == other.shape[i] || other.shape[i] == 1)) {
                throw std::invalid_argument("Incompatible shapes for broadcasting");
            }
        }
        
        // 遍历当前张量的每个元素
        for (unsigned int i0 = 0; i0 < shape[0]; i0++) {
            unsigned int other_i0 = (other.shape[0] == 1) ? 0 : i0;
            
            for (unsigned int i1 = 0; i1 < shape[1]; i1++) {
                unsigned int other_i1 = (other.shape[1] == 1) ? 0 : i1;
                
                for (unsigned int i2 = 0; i2 < shape[2]; i2++) {
                    unsigned int other_i2 = (other.shape[2] == 1) ? 0 : i2;
                    
                    for (unsigned int i3 = 0; i3 < shape[3]; i3++) {
                        unsigned int other_i3 = (other.shape[3] == 1) ? 0 : i3;
                        
                        // 计算当前张量的线性索引
                        unsigned int this_index = get_linear_index(i0, i1, i2, i3);
                        
                        // 计算other张量的线性索引
                        unsigned int other_index = 
                            ((other_i0 * other.shape[1] + other_i1) * other.shape[2] + other_i2) 
                            * other.shape[3] + other_i3;
                        
                        // 执行加法操作
                        data[this_index] += other.data[other_index];
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
