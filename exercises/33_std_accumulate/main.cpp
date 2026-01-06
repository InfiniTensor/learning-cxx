#include "../exercise.h"
#include <array>
#include <numeric>
#include <algorithm>
#include <vector>
// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    std::vector<int> shape = {1, 3, 224, 224};
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    int size = std::accumulate(shape.begin(),shape.end(),4,[](int all,int now){
        return all*now;
    });
    std::cout << size << std::endl;
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
