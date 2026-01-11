#include "../exercise.h"
#include <cstring>

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    // 构造函数：初始化形状和数据
    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 1. 计算总大小并复制 shape
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        // 2. 申请内存并拷贝数据
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 单向广播加法
    Tensor4D &operator+=(Tensor4D const &others) {
        // 1. 预先计算哪些维度需要广播（即 others 的对应维度为 1，但 this 不是 1）
        bool broadcast[4];
        for (int i = 0; i < 4; ++i) {
            // 如果形状不同，意味着 others 必须广播（题目保证 others 维度如果不匹配则必为 1）
            broadcast[i] = (shape[i] != others.shape[i]);
        }

        auto dst = this->data;  // 写入位置
        auto src = others.data; // 读取位置
        
        // 标记数组 (marks)：用于记录每一层循环开始时 src 的指针位置
        // 这样当需要广播（回退）时，就能找到回退的点
        T *marks[4] = {src, nullptr, nullptr, nullptr};

        // 2. 四层循环遍历大张量 (this)
        for (unsigned int i0 = 0; i0 < shape[0]; ++i0) {
            // 如果第 0 维广播，指针回到本层起点
            if (broadcast[0]) src = marks[0]; 
            marks[1] = src; // 记录下一层的起点

            for (unsigned int i1 = 0; i1 < shape[1]; ++i1) {
                if (broadcast[1]) src = marks[1];
                marks[2] = src;

                for (unsigned int i2 = 0; i2 < shape[2]; ++i2) {
                    if (broadcast[2]) src = marks[2];
                    marks[3] = src;

                    for (unsigned int i3 = 0; i3 < shape[3]; ++i3) {
                        if (broadcast[3]) src = marks[3];

                        // 核心计算：对应位置相加
                        *dst += *src;

                        // 移动指针
                        dst++;
                        src++;
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
        auto t0 = Tensor4D<int>(shape, data);
        auto t1 = Tensor4D<int>(shape, data);
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

        auto t0 = Tensor4D<float>(s0, d0);
        auto t1 = Tensor4D<float>(s1, d1);
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

        auto t0 = Tensor4D<double>(s0, d0);
        auto t1 = Tensor4D<double>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}