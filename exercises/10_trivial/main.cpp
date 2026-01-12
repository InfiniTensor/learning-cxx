#include "../exercise.h"
#include <cstddef>

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};


static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    ASSERT((std::size_t)i <= (sizeof(cache.cache) / sizeof(*cache.cache)), "out of cache range");
    int& cached = cache.cached;
    for (; cached <= i; cached++) {
        cache.cache[cached] = cache.cache[cached - 1] + cache.cache[cached - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    FibonacciCache fib{{0, 1}, 2};
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
