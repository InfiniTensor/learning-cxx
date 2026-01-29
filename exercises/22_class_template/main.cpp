#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];  // 存储四个维度信息
    T *data;

    Tensor4D(unsigned int *shape_, T const *data_) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for (int i = 0; i < 4; ++i)
        {
            shape[i] = shape_[i];
            size *= shape_[i];  // 总的元素数量
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
        // 形状不同的长度必须为1
        // 1.检查维度
        int i,idx = 1,thissize = 1,othersize = 1;    // 第i个维度存在元素
        int flag_dim = -1,beforesize = 1;
        for (i = 0; i < 4; ++i) {
            if(flag_dim == -1 && shape[i] !=  others.shape[i])
            {
                flag_dim = i;  // 设置不同维度时的维度坐标
            }
            if(flag_dim == -1)
            {
                beforesize *= shape[i]; // 记录this的元素个数
            }
            thissize *= this->shape[i];
            othersize *= others.shape[i];     // 计算起始位置以及终止位置
        }
        // 一、不进行广播
        if (flag_dim == -1) {
            for (int i = 0; i < thissize; ++i) {
                data[i] += others.data[i];
            }
            return *this;
        }
        std::cout << "thissize:" << thissize << std::endl;
        std::cout << "othersize:" << othersize << std::endl;
        std::cout << "idx:" << idx << std::endl;

        // 将4维shape 2维化
        int step = 1,other_step = 1 ;
        std::cout << "flag_dim" << flag_dim << std::endl;
        for (int i = 3; i >= flag_dim; --i) {
            step *= shape[i];
            other_step *= others.shape[i];
        }
        //std::cout << "step:" << other_step << std::endl;

        // 二、k 为batch，必须保证batch的维度相同
        for (int k = 0; k < beforesize; ++k) {
            for (int i = 0; i < step; ++i)// this:[2,3,4]. -> [2,1,12]  other:[2,1,4]
            {

                this->data[i + k * step] += others.data[(i + k * step) % other_step + k * other_step];// 1 -> 12 : 1  -> 4.
                //std::cout << "this_idx: " << i + k * step << std::endl;
                //std::cout << "other_idx: " << ((i + k * step) % other_step + k * other_step) % othersize  << std::endl;
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
