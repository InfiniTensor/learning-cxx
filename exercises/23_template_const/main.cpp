#include "../exercise.h"
#include <cstring>

// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>

template<unsigned int N, class T> // N是一个模板非类型实参，它是一个无符号整数常量，代表张量的维度数量
// N作为模板参数传入后，编译器在编译阶段就能确定数组shape[N]的大小，以及相关循环等，避免了运行时动态分配内存的开销。
/*
什么是模板非类型实参？
    模板参数除了类型参数外，还可以是值参数，比如整数、指针、引用等，这些就叫模板非类型实参。
    非类型模板参数允许在编译时传递常量信息，比如数组大小、维度数、编译期常量等。
    它的好处是编译器可以生成针对不同参数的专门代码，效率高，且能够做更多编译期检查。
*/
struct Tensor {  
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        // 在构造函数中复制shape数组、计算数据总大小（所有维度的乘积）以分配内存
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        // 分配内存并初始化数据
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }
    ~Tensor() {
        delete[] data; // 在析构函数中释放内存，避免内存泄漏
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) { 
        return data[data_index(indices)];  // 数据存储使用一维数组，结合 data_index 函数实现多维索引到一维索引的映射（采用行主序计算）。
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

// private: 避免 data_index 被外部调用，确保它只在类内部使用
// 计算多维索引到一维数组的映射
// 注意：这里假设是行主序存储，即最后一维变化最快
// 例如，shape = {2, 3, 4}，data_index([1, 2, 3]) = 1 * (3 * 4) + 2 * (4) + 3 = 1 * 12 + 2 * 4 + 3 = 12 + 8 + 3 = 23
public: 
/*
这样才可以打印
tensor[0,0,0] = 1
Linear index for [0,0,0] = 0
tensor[3,4,99] = 2
Linear index for [3,4,99] = 3683
张量的值赋值和访问：
张量的索引（如 tensor[0, 0, 0]）用来表示张量中具体位置的值。
    tensor[0, 0, 0] = 1 表示你在张量的索引 [0, 0, 0] 处赋值为 1。
    tensor[3, 4, 99] = 2 表示你在张量的索引 [3, 4, 99] 处赋值为 2。
线性索引（一维下标）的计算：
线性索引（如 3683）是将多维索引转换成一维数组下标后得到的结果。在内存中，张量的元素会按这个线性顺序存储。
这样就能有效地将多维数据存储到一维数组中，避免了复杂的多维数组结构，同时也能利用计算机的缓存和内存优化。
    Linear index for [0, 0, 0] = 0 表示在存储张量数据时，索引 [0, 0, 0] 对应的一维下标是 0。
    Linear index for [3, 4, 99] = 3683 表示在存储张量数据时，索引 [3, 4, 99] 对应的一维下标是 3683。
假设张量的形状是 shape[] = {7, 8, 128}，即有 7 层，每层有 8 行，每行有 128 列。
    计算一维下标：假设张量存储顺序是行主序（Row-major），计算一维下标的方法是：index = i0 * (8 * 128) + i1 * 128 + i2
    i0 * (8 * 128) 是第一维（7）对一维下标的偏移量，即前面有多少个完整的二维块。
    i1 * 128 是第二维（8）对一维下标的偏移量，即该层的前几行。
    i2 是第三维（128）的偏移量，即该行的列。
张量的内存布局（行主序）
在行主序（Row-major）布局下，内存中张量数据的顺序是从最外层维度到最内层维度排列。具体地说：
    第一维（7）表示层数
    第二维（8）表示每层的行数
    第三维（128）表示每层的列数
*/
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1; // 步长初始化为1
        // 计算一维下标
        /*
        这其实是列主序（Column-major），也就是从最内层维度到外层维度，
        而题目使用的是行主序（Row-major），应该从外层维度到内层维度，也就是从最后一维开始往前计算。
        */
        /*
        for (unsigned int i = 0; i < N; ++i) {
            ASSERT(indices[i] < shape[i], "Invalid index");
             TODO: 计算 index
           
            根据张量的shape和输入的多维索引，计算出data的一维下标
            index += indices[i] * stride; // 计算当前维度的偏移量
            stride *= shape[i]; // 更新步长 
            
        }
        */
        for (int i = N - 1; i >= 0; --i) {  // 注意 int i = N - 1 是 倒序循环，要用 int，否则无符号整型在 i-- 时可能溢出。
            ASSERT(indices[i] < shape[i], "Invalid index");
            index += indices[i] * stride; // 计算当前维度的偏移量
            stride *= shape[i]; // 更新步长
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
        tensor[i0] = 1; // 设置张量中第一个元素的值为1
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
        /*
        张量的内存存储遵循 行主序（Row-major）规则，即先存储外层维度，再存储内层维度。所以，三维张量 shape[] = {7, 8, 128} 中的每个元素按照这样的顺序存储在内存中：
        张量的第一维（7）表示的是层数。
        第二维（8）表示的是每一层的行数。
        第三维（128）表示的是每一层的列数。
        */
        /*
        计算一维下标：假设张量存储顺序是行主序（Row-major），计算一维下标的方法是：index = i0 * (8 * 128) + i1 * 128 + i2
        i0 * (8 * 128) 是第一维（7）对一维下标的偏移量，即前面有多少个完整的二维块。
        i1 * 128 是第二维（8）对一维下标的偏移量，即该层的前几行。
        i2 是第三维（128）的偏移量，即该行的列。
        */
        unsigned int i0[]{0, 0, 0}; // 第一个索引i0对应张量中的(0,0,0)
        tensor[i0] = 1.f; // 设置张量中第一个元素的值为1
        std::cout << "tensor[" << i0[0] << "," << i0[1] << "," << i0[2] << "] = " << tensor[i0] << std::endl;
        std::cout << "Linear index for [" << i0[0] << "," << i0[1] << "," << i0[2] << "] = " << tensor.data_index(i0) << std::endl;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99}; // 第二个索引i1对应张量中的(3,4,99)
        tensor[i1] = 2.f;   // 设置张量中第二个元素的值为2
        std::cout << "tensor[" << i1[0] << "," << i1[1] << "," << i1[2] << "] = " << tensor[i1] << std::endl;
        unsigned int linear_index = tensor.data_index(i1); // 计算一维下标
        std::cout << "Linear index for [" << i1[0] << "," << i1[1] << "," << i1[2] << "] = " << linear_index << std::endl;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2"); 
        /*
        tensor[i1] = 2.f; 中的索引 i1[] = {3, 4, 99} 表示：
        第一维索引 3 表示该位置属于第4层（层索引从0开始）。
        第二维索引 4 表示该层的第5行。
        第三维索引 99 表示该行的第100列。

        index = 3 * (8 * 128) + 4 * 128 + 99
        index = 3 * 1024 + 4 * 128 + 99
        index = 3072 + 512 + 99
        index = 3683
        这个计算表明，在存储顺序为行主序的情况下，tensor[3, 4, 99] 对应的一维下标是 3683。
        */
    }
    return 0;
}
