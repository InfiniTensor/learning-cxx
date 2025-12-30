#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        ASSERT(sizeof(vec) == sizeof(std::vector<int>), "Fill in the correct value.");
        /*
        为什么不是 20？
        sizeof(vec) 并不等于 20，
        因为 20 是容器中存储元素的总字节数（5 * sizeof(int)，假设 sizeof(int) 为 4 字节）。
        但 sizeof(vec) 返回的是容器对象本身的内存大小，而不是它存储的元素的内存大小。
        */
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(std::vector<double>), "Fill in the correct value.");
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(std::vector<double>), "Fill in the correct value.");
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(std::vector<double>), "Fill in the correct value.");
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1, "Fill in the correct value.");
            ASSERT(vec[1] == 2, "Fill in the correct value.");
            ASSERT(vec[2] == 3, "Fill in the correct value.");
            ASSERT(vec[3] == 4, "Fill in the correct value.");
            ASSERT(vec[4] == 6, "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            /*
            在末尾插入或删除元素:push_back 和 pop_back 的时间复杂度是 O(1)（摊销时间复杂度），因为通常不需要移动其他元素。
            在中间或开始插入或删除元素:插入 (insert) 和删除 (erase) 的时间复杂度是 O(n)，因为这些操作可能会导致需要移动大量元素。
            扩容: 扩容操作的最坏时间复杂度为 O(n)，但是平均摊销时间复杂度为 O(1)，因为扩容次数相对较少。
            缩容: shrink_to_fit 通常会是 O(n) 的时间复杂度，视具体实现而定。
            */
            vec.insert(vec.begin() + 1, 1.5); // 在 vec 的第二个位置插入 1.5
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            vec.erase(vec.begin() + 1); // 删除第二个位置的元素
            // ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
            ASSERT((vec == std::vector<double>{1, 2, 3, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit(); // 调整容量以适应当前大小
            ASSERT(vec.capacity() == 5, "Fill in the correct value."); // 容量调整为实际大小
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value."); // 清空后大小为0
            ASSERT(vec.capacity() == 5, "Fill in the correct value."); // 清空后容量不变
        }
    }
    {
        std::vector<char> vec(48, 'z'); // TODO: 调用正确的构造函数 
        // 创建一个包含 48 个 'z' 的 vector
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        // ASSERT(sizeof(vec) == 48 * sizeof(char), "Fill in the correct value.");
        ASSERT(sizeof(vec) == sizeof(std::vector<char>), "Fill in the correct value.");
        // 打印48 * sizeof(char)
        std::cout << "Size of 48 * sizeof(char): " << 48 * sizeof(char) << std::endl; // 48 * sizeof(char) = 48
        // 打印sizeof(vec)
        std::cout << "Size of vec: " << sizeof(vec) << std::endl; // sizeof(vec) = sizeof(std::vector<char>)，24 
        // 打印sizeof(std::vector<char>)
        std::cout << "Size of std::vector<char>: " << sizeof(std::vector<char>) << std::endl; // sizeof(std::vector<char>) = 24 字节
        // 获取std::vector<char>容器的数据部分所占用内存，可以用vec.capacity() * sizeof(char)，它会告诉你容器为存储元素预留的内存大小。
        /*
        但要注意，vec.capacity() 和 vec.size() 可能不同：
        capacity() 是容器为存储元素而预留的内存空间的大小，可能大于 size()，用于优化内存分配，减少重新分配内存的次数。
        size() 是容器当前存储的元素个数。
        打印size
        */
        std::cout << "Size in vec: " << vec.size() << std::endl;
   
        std::cout << "Size of data in vec: " << vec.capacity() * sizeof(char) << std::endl; // vec.capacity() * sizeof(char) = 48 字节
        // 打印容器当前存储的元素个数
        
        /*
sizeof(std::vector<char>) 和 sizeof(vec) 是 24 字节：
std::vector 是一个容器类，它包含一些 元数据，包括：
    一个指向存储元素的内存块的指针（通常为 8 字节，指针的大小取决于架构）。
    存储元素的数量（size），通常为 4 字节（对于 int 类型，假设大小是 4 字节）。
    存储容量（capacity），通常也是 4 字节（与 size 同类型）。
所以，std::vector<char> 的大小通常是 24 字节（8 字节的指针 + 4 字节的 size + 4 字节的 capacity），这取决于平台和编译器的实现。
如果你在 64 位系统上，指针通常是 8 字节，整型（size 和 capacity）是 4 字节。

48 * sizeof(char) 是 48 字节：
sizeof(char) 是 1 字节，所以 48 * sizeof(char) 等于 48 字节，表示存储 48 个 char 元素所需的内存大小。
这表示 std::vector<char> 在存储数据时需要的内存空间（假设每个 char 为 1 字节）。

为什么 sizeof(vec) 和 48 * sizeof(char) 不相等？
    sizeof(vec) 计算的是容器对象的内存占用，即 容器本身的大小，它并不包括容器内部存储数据所占用的内存。
        std::vector<char> 本身是一个管理动态数组的容器，它的大小只包含一些元数据（指针、容量和大小），而不包括它实际存储的数据。
    48 * sizeof(char) 计算的是容器为存储数据而分配的内存。它代表的是容器的数据部分（即实际存储的元素）所占用的内存空间。
*/
        {
            auto capacity = vec.capacity();
            vec.resize(16); // 调整大小为16。如果新大小小于当前大小，超出部分会被删除。如果新大小大于当前大小，多出来的元素会被默认初始化。
            ASSERT(vec.size() == 16, "Fill in the correct value."); // 调整大小为16
            ASSERT(vec.capacity() == capacity, "Fill in a correct identifier.");
        }
        {
            vec.reserve(256); // 预留空间为256，并不改变实际的大小。如果当前容量小于 256，它会扩展容量。
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a'); // 在末尾添加元素。如果 vector 没有足够的空间，会重新分配更大的内存。
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "Fill in the correct value."); 
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
            ASSERT(vec[15] == 'z', "Fill in the correct value.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}
