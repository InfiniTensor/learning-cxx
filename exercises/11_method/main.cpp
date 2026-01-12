#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    unsigned long long get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i]; 
    }
};

int main(int argc, char **argv) {
    Fibonacci fib{{0, 1}, 2};
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
