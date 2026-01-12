#include "../exercise.h"
#include "./memory_region.cpp"
#include <iostream>


/*
// 注：/proc/maps 中 .data/.bss 常合并为 Data
// 强类型枚举：内存区域（对应原测试代码的 DATA/BSS/STACK/HEAP/TEXT 等）
enum class MemRegion : uint8_t {
    Unknown = 0,  // 未知区域
    Text,         // .text 代码段 (对应原 TEXT)
    RoData,       // .rodata 只读数据段 (字符串字面量/全局常量)
    Data,         // .data 数据段 (已初始化全局变量和静态变量)
    Bss,          // .bss 段 (未初始化全局变量和静态变量)
    Stack,        // 栈 (对应原 STACK)
    Heap          // 堆 (对应原 HEAP)
};
*/

// 测试变量
int global_var = 1;                
int global_var_uninit;             
static int static_global_var = 2; 
const int global_const = 3;        


// 测试函数（代码段）
void test_func() {}

int main() {
    int local_var = 4;                 
    static int static_local_var = 5;   
    const int local_const = 6;         
    int* heap_var = new int(7);        
    const char* str_literal = "hello";              

  
    // TODO: 将下列 `?` 替换为正确的值

    // 测试1: 全局变量
    ASSERT(get_memory_region(&global_var) == MemRegion::Data, "Error in judging the location of global_var");
    
    // 测试2: 静态全局变量 
    ASSERT(get_memory_region(&static_global_var) == ?,"Error in judging the location of static_global_var");
    
    // 测试3: 全局常量 
    ASSERT(get_memory_region(&global_const) == ?,"Error in judging the location of global_const");
    
    // 测试4: 局部变量 
    ASSERT(get_memory_region(&local_var) == ?, "Error in judging the location of local_var");
    
    // 测试5: 静态局部变量 
    ASSERT(get_memory_region(&static_local_var) == ?,"Error in judging the location of static_local_var");
    
    // 测试6: 局部常量 
    ASSERT(get_memory_region(&local_const) == ?,"Error in judging the location of local_const");
    
    // 测试7: 堆分配的内存 
    ASSERT(get_memory_region(heap_var) == ?,"Error in judging the location of heap_var");
    
    // 测试8: 字符串字面量 
    ASSERT(get_memory_region(str_literal) == ?,"Error in judging the location of str_literal");
    
    // 测试9: 堆指针本身 
    ASSERT(get_memory_region(&heap_var) == ?,"Error in judging the location of &heap_var");

    // 测试10：未初始化全局变量 
    ASSERT(get_memory_region(&global_var_uninit) == ?,"Error in judging the location of global_var_uninit");

    // 测试11：函数地址 
    ASSERT(get_memory_region(reinterpret_cast<const void*>(test_func)) == ?,"Error in judging the location of test_func");
    
    delete heap_var;
    heap_var = nullptr;
    return 0;
}


