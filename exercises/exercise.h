#ifndef __EXERCISE_H__
#define __EXERCISE_H__

#include <iostream>

#define ASSERT(COND, MSG)                                                                         \
    if (!(COND)) {                                                                                \
        std::cerr << "\x1b[31mAssertion failed at line #" << __LINE__ << ": \x1b[0m" << std::endl \
                  << std::endl                                                                    \
                  << #COND << std::endl                                                           \
                  << std::endl                                                                    \
                  << "\x1b[34mMessage:\x1b[0m" << std::endl                                       \
                  << std::endl                                                                    \
                  << MSG << std::endl                                                             \
                  << std::endl;                                                                   \
        exit(1);                                                                                  \
    }

#endif// __EXERCISE_H__

/*std::cerr 
把错误信息和正常输出分开方便调试。

在脚本或重定向时，可以把错误输出单独保存或显示。

std::cerr 默认不带缓冲（unbuffered），输出内容更及时，适合打印错误和警告。
*/