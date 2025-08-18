#include "../exercise.h"

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    Fibonacci() {
        cache[0] = 0;
        cache[1] = 1;
        cached = 2;
    }

    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}