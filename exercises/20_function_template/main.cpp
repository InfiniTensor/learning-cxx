#include "../exercise.h"
#include <cmath>

template<typename T>
T plus(T a, T b) { return a + b; }

int main(int, char**) {
    ASSERT(plus(1,   2)   == 3,   "Plus two int");
    ASSERT(plus(1u,  2u)  == 3u,  "Plus two unsigned int");
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");

    // 近似相等
    auto eps = 1e-12;
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < eps, "How to make this pass?");
    return 0;
}