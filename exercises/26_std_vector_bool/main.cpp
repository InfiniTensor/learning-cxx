#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>
/*
模板特化（Template Specialization）是 C++ 中的一个重要特性，
它允许你为特定类型或类型组合提供自定义的实现。这意味着，当某个类型参数符合特定条件时，编译器将选择一个不同的实现，而不是使用通用的模板实现。
template <typename T>
void func(T t) {
    std::cout << "General template" << std::endl;
}

template <>
void func<int>(int t) {
    std::cout << "Specialized template for int" << std::endl;
}

int main() {
    func(10);  // 调用特化版本
    func(3.14);  // 调用通用模板
}

Specialized template for int
General template
这里，func<int> 是对 func 模板的特化，当模板参数是 int 时，调用特化版本。
*/
// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    /*
    std::vector<bool> vec(100, true); 这行代码创建了一个大小为 100 的 std::vector<bool>，并且将每个元素初始化为 true。
        100 表示 std::vector<bool> 的大小，即 vec 将包含 100 个布尔值。
        true 是每个布尔值的初始值，因此 vec 中的所有元素在创建时都会被初始化为 true。
    */
    /*
    位压缩： std::vector<bool> 并不像其他类型的 std::vector 那样每个元素都占用一个字节，而是通过位压缩的方式，
    将每个布尔值存储在单独的比特（bit）中。这种实现方式节省了内存空间，但也带来了一些特殊的行为，例如，它返回的是代理对象而非直接的引用。
    内存管理： 在大规模数据处理时（如交易数据、市场深度等），通过使用 std::vector<bool>，你可以显著降低内存使用。
    在涉及大量布尔数据时，这一点尤其重要。

    事件触发：
    在系统中，事件触发可以用布尔值表示。例如，当某个市场的价格触发了预设的条件时，可以在 std::vector<bool> 中设置对应的标志。
    这些布尔值可以快速用于判断是否需要执行进一步的操作。
    std::vector<bool> 在这种情况下能够提高对实时数据的处理效率，特别是当数据规模庞大时，
    使用 std::vector<bool> 代替 std::vector<int> 或 std::vector<char> 能够节省大量的内存。
    */
    // vec(100, true) 创建一个大小为 100 的 std::vector<bool>，并将所有元素初始化为 true。
    ASSERT(vec[0], "Make this assertion pass."); 
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    /*
    这一部分指的是 sizeof(std::vector<bool>) 的值可能在不同的平台或编译器下有所不同。在某些平台上，例如 CI 环境（Continuous Integration，持续集成环境）中的 Ubuntu 系统，std::vector<bool> 的大小可能会有所不同，因为其实现与平台和编译器有关。
    平台相关性：std::vector<bool> 的实现依赖于编译器的特性和系统架构。一些编译器可能会在内存上进行优化，使得它在内存中占用更少的空间。这是因为 std::vector<bool> 采用了位压缩技术来节省空间，每个布尔值通常存储在一个比特（bit）中，而不是占用一个字节（byte）。
    CI:Ubuntu：这部分提示用户，在 Ubuntu 系统或 CI 环境中，这种差异可能会对 sizeof(std::vector<bool>) 的值产生影响，因此需要注意不同平台下的大小。
    */
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    /*
    sizeof(std::vector<bool>) 返回的是 std::vector<bool> 类型的大小，
    这个大小通常会包含容器的元数据（如指针、大小、容量等）。
    由于 std::vector<bool> 使用了位压缩（每个布尔值只占用 1 位），它的实际实现方式与普通 std::vector 不同。
    因此，sizeof(std::vector<bool>) 的值通常是固定的，而不是与向量的元素个数直接相关。
    */
    std::cout << "sizeof(vec) = " << sizeof(vec) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value."); 
    /*
    sizeof(std::vector<bool>) 返回的是 std::vector<bool> 对象本身占用的内存大小，包括内部实现的额外信息（如指针、大小、容量等）。
    在大多数编译器实现中，std::vector<bool> 并没有像普通类型 std::vector<T> 那样，每个元素都占用一个字节，因此总的内存占用可能较小，约为 32 字节。
    这32字节的原因是，由于 std::vector<bool> 内部实现采用了压缩位的方式，但仍然要包含一些必要的元数据。例如：
        对象的大小（可能是 4 或 8 字节，取决于平台）
        内部的指针（指向数据的存储位置）
        容量、大小等其他信息。
    */
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
        /*
        这里我们将 vec[20] 设置为 false，然后验证它是否真的变成了 false。
        由于 std::vector<bool> 是一个特化实现，其元素是通过代理对象访问的。
        因此，这里的 vec[20] 可能会通过一个 代理对象 返回，而这个代理对象负责管理底层位的操作。
        你不能直接获取 bool& 引用，而是会得到一个临时对象，它封装了对底层数据的访问。
        */
    }
    {
        vec.push_back(false); 
        /*
        在 vec 中插入一个新元素时，push_back 会增加向量的大小（size），并将元素值设置为 false。
        std::vector<bool> 是动态扩展的，因此push_back 增加其 大小。之后你需要验证新增的元素是否被正确添加，并且它的值确实是 false。
        */
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // 引用操作与代理对象
        auto ref = vec[30]; // 获取vec[30]的代理对象，而不是直接的 bool 引用。这个代理对象负责访问底层存储。
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 如果vec[30] 的值为 true，那么ref也为 true。

        // 修改ref，实际上修改的是 vec[30] 的底层位。
        ref = false; 
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`."); // 因为 ref 修改了 vec[30]，所以 vec[30] 的值也变成了 false。
        /*
        为什么代理对象的修改会影响底层数据？
        代理对象会在修改时操作底层存储的数据位（位图），这种修改会反映到 std::vector<bool> 容器中。
        所以，ref = false 不仅会修改代理对象 ref 的值，也会同步修改底层存储中的第 30 个布尔值。
        */
        /*
        std::vector<bool> 是 std::vector 的一个特化版本，用于存储布尔值 (bool)。
        与其他类型（如 int、char）不同，std::vector<bool> 会进行 位压缩，即每个布尔值只占用 1 位而不是 1 字节。
        因此，当访问 vec[30] 时，实际返回的是一个代理对象，而不是直接的 bool& 引用。
        '!vec[30]是对 vec[30] 的 逻辑取反。
        如果 vec[30] 是 true，那么 !vec[30] 会变成 false；如果 vec[30] 是 false，那么 !vec[30] 会变成 true。
        由于 std::vector<bool> 使用代理对象来返回每个元素，vec[30] 返回的是该代理对象的值。因此，!vec[30] 会检查该元素的布尔值是否为 false。
        这里的断言是检查 vec[30] 是否为 false。如果 vec[30] 的值是 true，则断言失败，程序会终止并输出 "Fill in vec[30]or!vec[30]." 的错误信息。
        */
    }
    return 0;
}
/*
由于 std::vector<bool> 是对 bool 类型的模板特化，内部的 元素 是通过 代理对象 访问的。
每次访问 std::vector<bool> 中的元素，实际上返回的是一个包装对象（即代理对象），它负责对底层位的操作。代理对象的行为包括：
    返回值：它返回一个 临时对象，而不是 bool& 引用。
    修改值：它通过位运算操作来修改底层数据存储的比特。
*/