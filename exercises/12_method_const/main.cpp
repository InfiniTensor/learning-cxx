#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];

    constexpr Fibonacci() : numbers{0, 1, 1} {}

    constexpr Fibonacci(const int (&arr)[11]) : numbers{} {
        for (int i = 0; i < 11; ++i) {
            numbers[i] = arr[i];
        }
    }

    constexpr int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    constexpr int INIT[11] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    constexpr Fibonacci FIB(INIT);
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
