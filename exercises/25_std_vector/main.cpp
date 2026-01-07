#include "../exercise.h"
#include <cstring>
#include <vector>

int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // 在 64 位系统上通常是 24 字节（3 个指针）
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "sizeof vector object doesn't change.");
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "sizeof vector object doesn't change.");
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
            // insert 第一个参数是迭代器。vec.begin() + 1 指向第二个位置
            vec.insert(vec.begin() + 1, 1.5);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            // erase vec.begin() + 3 指向元素 3 (索引为3)
            vec.erase(vec.begin() + 3);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            // clear 不一定会改变 capacity
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
        }
    }
    {
        // 调用构造函数：48个元素，每个都是 'z'
        std::vector<char> vec(48, 'z');
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        {
            auto capacity = vec.capacity();
            vec.resize(16);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == capacity, "Resize smaller doesn't change capacity.");
        }
        {
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Reserve doesn't change size.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "16 + 4 = 20");
            ASSERT(vec.capacity() == 256, "Capacity is still 256.");
            ASSERT(vec[15] == 'z', "Original elements remain.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}