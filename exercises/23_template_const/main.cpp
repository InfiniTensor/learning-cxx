#include "../exercise.h"
#include <cstring>

// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for(unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];   // 复制 shape
            size *= shape_[i];      // 累乘得到总大小
        }

        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }
    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        for (unsigned int i = 0; i < N; ++i) {
            ASSERT(indices[i] < shape[i], "Invalid index");
            // TODO: 计算 index
            index = index * shape[i] + indices[i];  // 迭代公式
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    // 测试用例 1: 4 维整型张量
    {
        // 创建 shape 为 {2, 3, 4, 5} 的 4 维张量，总元素数 = 2*3*4*5 = 120
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        // 测试索引 {0,0,0,0} -> 线性索引 0
        // 计算: ((0*2+0)*3+0)*4+0)*5+0 = 0
        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        // 测试索引 {1,2,3,4} -> 线性索引 119
        // 计算: ((0*2+1)*3+2)*4+3)*5+4 = ((1*3+2)*4+3)*5+4 = (5*4+3)*5+4 = 23*5+4 = 119
        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    // 测试用例 2: 3 维浮点型张量
    {
        // 创建 shape 为 {7, 8, 128} 的 3 维张量，总元素数 = 7*8*128 = 7168
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        // 测试索引 {0,0,0} -> 线性索引 0
        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        // 测试索引 {3,4,99} -> 线性索引 3683
        // 计算: (0*7+3)*8+4)*128+99 = (3*8+4)*128+99 = 28*128+99 = 3584+99 = 3683
        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
