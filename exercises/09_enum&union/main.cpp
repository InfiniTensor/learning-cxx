#include "../exercise.h"

// READ: 枚举类型 <https://zh.cppreference.com/w/cpp/language/enum>

// enum（枚举）是一种用户自定义的数据类型，用于为一组`整数常量`分配好听的名字。使用枚举可以让代码更具可读性和可维护性。

// `enum` 是 C 的兼容类型，本质上其对应类型的常量。
// 在 `enum` 中定义标识符等价于定义 constexpr 常量，
// 这些标识符不需要前缀，可以直接引用。
// 因此 `enum` 定义会污染命名空间。

// 不限定作用域枚举，不推荐作法
// 可以实现隐式转换：int x =Red
enum ColorEnum : unsigned char {
    COLOR_RED = 31,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
};

// 有作用域枚举型是 C++ 引入的类型安全枚举。
// 其内部标识符需要带前缀引用，如 `Color::Red`。
// 作用域枚举型可以避免命名空间污染，并提供类型安全保证。

// 限定作用域枚举，推荐做法
// 使用时必须带上类名（作用域）
// TrafficLight s = TrafficLight::RED;
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

ColorEnum convert_by_pun(Color c) {
    // READ: <https://zh.cppreference.com/w/cpp/language/union>
    // `union` 表示在同一内存位置存储的不同类型的值。
    // 其常见用法是实现类型双关转换，即将一种类型的值转换为另一种无关类型的值。
    // 但这种写法实际上仅在 C 语言良定义，在 C++ 中是未定义行为。
    // 这是比较少见的 C++ 不与 C 保持兼容的特性。
    // READ: 类型双关 <https://tttapa.github.io/Pages/Programming/Cpp/Practices/type-punning.html>

    //union（联合体/共用体）是 C++ 中一种特殊的类类型。它最显著的特征是：所有成员共享同一块内存地址
    //但在同一时刻只能使用其中的一个成员，这就意味着数据会被覆盖，是一种极端节省内存的写法
    union TypePun {
        ColorEnum e;
        Color c;
    };

    TypePun pun;
    // TODO: 补全类型双关转换
    pun.c = c;//c值写入，e值被覆盖
    return pun.e;
}

int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}
