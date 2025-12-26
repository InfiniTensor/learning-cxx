#include "../exercise.h"
#include <cstring>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];  // 存储各维度大小
    T *data;                // 线性存储的张量数据

    // 构造函数：初始化形状、分配内存并置0
    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // 复制输入形状到成员变量
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];  // 计算总元素数（各维度乘积）
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));  // 初始化为0
    }
    
    ~Tensor() {
        delete[] data;  // 释放动态内存
    }

    // 禁止复制和移动，避免资源管理问题
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    // 重载[]运算符，支持多维索引访问
    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    // 将多维索引转换为线性索引
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1;  // 步长：当前维度每个元素对应的内存偏移
        
        // 从最后一个维度开始计算（行优先存储）
        for (int i = N - 1; i >= 0; --i) {
            ASSERT(indices[i] < shape[i], "Invalid index");  // 索引越界检查
            
            // 累加当前维度的偏移
            index += indices[i] * stride;
            
            // 计算前一个维度的步长（当前维度大小 × 当前步长）
            if (i > 0) {
                stride *= shape[i];
            }
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
