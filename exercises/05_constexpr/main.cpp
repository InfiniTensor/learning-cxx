#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
	if(i == 0) return 0;
	if(i == 1) return 1;
	int n = i;		
	unsigned long long a = 0, b = 1;
	for(int i = 2; i <= n; i ++){
		unsigned long long next = a + b;
		a = b;
		b = next;
	}
	return b;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 90;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
