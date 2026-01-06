#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int shape_[4], T *data_) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        std::memcpy(shape, shape_, sizeof(unsigned int )*4);
        for (int i = 0; i < 4; ++i) {
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
        unsigned int size=1;
        unsigned int othersize=1;
        unsigned int stride[4];
        unsigned int otherstride[4];
        unsigned int dim[4];
        for (int i = 3; i >=0; i--){
            stride[i]=size;
            otherstride[i]=othersize;
            size*=shape[i];
            othersize*=others.shape[i];
        }
        for (int i = 3; i >=0; i--) {
            ASSERT(shape[i] == others.shape[i] || (shape[i] != 1 && others.shape[i] == 1),"incompatible shape");
            if(shape[i]==others.shape[i])dim[i]=1;
            else dim[i]=0;
            }
        for(int i=0;i<shape[0];i++)
            for(int j=0;j<shape[1];j++)
                for(int k=0;k<shape[2];k++)
                    for(int m=0;m<shape[3];m++)
                        data[i*stride[0]+j*stride[1]+k*stride[2]+m*stride[3]]+=others.data[i*otherstride[0]*dim[0]+j*otherstride[1]*dim[1]+k*otherstride[2]*dim[2]+m*otherstride[3]*dim[3]];
                        
                    
        return *this;
        
    
};
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
        Tensor4D<int> t0(shape, data) ;
        Tensor4D<int> t1(shape, data) ;
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]={1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]={1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        Tensor4D<float> t0(s0, d0);
        Tensor4D<float> t1(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] -7.f<=1e-9, "Every element of t0 should be 7 after adding t1 to it.");
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

        Tensor4D<double>t0(s0, d0);
        Tensor4D<double>t1(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
