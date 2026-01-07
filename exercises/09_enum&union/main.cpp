#include "../exercise.h"

// 非作用域枚举
enum ColorEnum : unsigned char {
    COLOR_RED = 31,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
};

// 有作用域枚举型
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

ColorEnum convert_by_pun(Color c) {
    union TypePun {
        ColorEnum e;
        Color c;
    };

    TypePun pun;
    // TODO: 补全类型双关转换
    // 将 Color 类型的值写入联合体成员 c
    pun.c = c;

    // 从同一内存位置读取为 ColorEnum 类型
    // 虽然在 C++ 中是未定义行为，但内存中它们共享起始地址
    return pun.e;
}

int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}