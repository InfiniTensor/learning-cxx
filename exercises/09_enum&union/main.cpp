#include "../exercise.h"

// READ: 枚举类型 <https://zh.cppreference.com/w/cpp/language/enum>

// `enum` 是 C 的兼容类型，本质上其对应类型的常量。
// 在 `enum` 中定义标识符等价于定义 constexpr 常量，
// 这些标识符不需要前缀，可以直接引用。
// 因此 `enum` 定义会污染命名空间。
// 在C++中，普通的枚举（enum）定义的常量会直接进入所在作用域
enum ColorEnum : unsigned char {
    COLOR_RED = 31,  // 标识符会直接放入当前作用域，通常是全局作用域
    COLOR_GREEN,     // 可能与其他变量或函数名称冲突
    COLOR_YELLOW,    // 如果其他地方也定义了一个变量或函数名为COLOR_YELLOW，就会命名冲突
    COLOR_BLUE,      // int COLOR_BLUE = 3，会覆盖枚举中的常量，造成代码混乱，开发者难追踪和调试
};

// 有作用域枚举型是 C++ 引入的类型安全枚举。
// 其内部标识符需要带前缀引用，如 `Color::Red`。
// 作用域枚举型可以避免命名空间污染，并提供类型安全保证。
// enum class: 作用域枚举，常量被限定在枚举类型本身的作用域内，这样就避免与其他部分的标识符冲突
// Red = COLOR_RED并不会直接进入全局作用域。要访问它们，必须通过作用域来引用
// Color color = Color::Red; 使用Color::Red来访问，这种方式确保了在枚举类型内的常量不会污染外部命名空间，也不会和其他标识符发生冲突。
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};
/*
普通的enum可以隐式转换为其底层类型（通常是整数类型），会有类型安全问题
enum Color { Red = 1, Green, Blue };
Color c = Red;
int x = c;  // 这在 C++ 中是允许的，可能会带来错误

然而，enum class 不允许这样直接的隐式转换，它提供了类型安全性。你不能直接将一个 enum class 类型的值赋给一个整数或其他类型的变量：
enum class Color { Red = 1, Green, Blue };
Color c = Color::Red;
int x = c;  // 错误：不能直接转换
如果你需要将 enum class 的值转换为整数，你必须显式地进行转换：
int x = static_cast<int>(c);  // 这样才是合法的
这种类型安全机制使得代码更加可靠，避免了错误的类型转换和不必要的隐式转换。

对于 enum class，你可以明确指定它的底层类型（如 int、unsigned char 等），这有助于在需要时进行更严格的类型控制。例如：
enum class Color : unsigned char { Red, Green, Blue };
这意味着 Color 类型的底层数据存储为 unsigned char 类型，这可以有效地控制内存的使用，并且防止出现不符合预期的类型行为。
*/

ColorEnum convert_by_pun(Color c) {
    // READ: <https://zh.cppreference.com/w/cpp/language/union>
    // `union` 表示在同一内存位置存储的不同类型的值。
    // 其常见用法是实现类型双关转换，即将一种类型的值转换为另一种无关类型的值。
    // 但这种写法实际上仅在 C 语言良定义，在 C++ 中是未定义行为。
    // 这是比较少见的 C++ 不与 C 保持兼容的特性。
    // READ: 类型双关 <https://tttapa.github.io/Pages/Programming/Cpp/Practices/type-punning.html>
    union TypePun {
        ColorEnum e;
        Color c;
    };

    TypePun pun;
    // TODO: 补全类型双关转换
    pun.c = c; // 将 Color 枚举值存储到 TypePun 的 c 成员中
    //return static_cast<ColorEnum>(c); // 显式类型转换, pass
    return pun.e;
}

int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}
