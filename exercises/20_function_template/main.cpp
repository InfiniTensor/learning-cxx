#include "../exercise.h"

template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    
    ASSERT(plus(0.1, 0.2) - 0.3 < 1E-9, "How to make this pass?");

    return 0;
}
