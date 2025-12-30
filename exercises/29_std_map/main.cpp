#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // TODO: 实现函数
    return map.find(key) != map.end();
    // map.find(key) 返回一个迭代器，如果 key 存在，则指向该键值对；如果 key 不存在，则指向 map 的 end()。
    // map.end() 是一个特殊的迭代器，表示 map 的末尾位置。
    // 因此，如果 map.find(key) != map.end()，则表示 key 存在于 map 中。
    // 这个函数的作用是检查给定的 key 是否存在于 map 中。
}

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // TODO: 实现函数
    // 使用 map 的 insert 或 operator[] 方法来设置键值对
    map[key] = value; // 使用 operator[] 设置键值对，如果 key 已存在，则会更新其对应的 value；如果 key 不存在，则会插入新的键值对。
    // 这种方式简洁且高效，适用于大多数场景。
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s); // 向 secrets 中添加键值对。
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`"); // 检查 secrets 这个 map 里是否存在键 "hello"，期望它存在。
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`"); // 检查 secrets 里是否不存在 "foo" 这个键，期望它不存在。

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s); // 更新 "hello" 的值为 "developer"
    ASSERT(secrets["hello"] == "developer", "hello -> developer"); // 检查 "hello" 的值是否已更新为 "developer"

    return 0;
}
/*
这段测试代码目的是验证 key_exists 和 set 函数的正确性：

    key_exists 函数能正确判断 map 中是否存在某个键。

    set 函数能正确插入新的键值对或更新已有键的值。

在交易系统开发中，类似这样的功能是基础操作，用来管理订单、行情、配置参数、缓存数据等。
*/
