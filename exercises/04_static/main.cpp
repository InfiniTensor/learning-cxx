#include "../exercise.h"

static int func(int param) {
    static int static_ = param;
    return static_++;
}

int main(int argc, char **argv) {
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}