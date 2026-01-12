#include <iostream>
#include <string>
#include <cstdint>
#include <cinttypes>
#include <vector>
#include <cstdio>
#include <cstring>

// 模拟 exercise.h 中的 ASSERT 宏（如果未定义则补充）
#ifndef ASSERT
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "断言失败: " << message << " (行号: " << __LINE__ << ")" << std::endl; \
            exit(EXIT_FAILURE); \
        } \
    } while (0)
#endif

// ====================== 内存区域检测核心逻辑（整合到当前文件，避免多文件依赖） ======================


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

// 内存映射条目结构体
struct MemoryMapEntry {
    uint64_t start_addr = 0;
    uint64_t end_addr = 0;
    char permissions[5] = {0};
    std::string region_type;

    MemoryMapEntry() = default;
};

// 核心检测类
class RegionDetector {
public:
    // 解析 /proc/self/maps 获取内存映射信息
    static std::vector<MemoryMapEntry> parseMemoryMaps() {
        std::vector<MemoryMapEntry> entries;
        FILE* fp = std::fopen("/proc/self/maps", "r");
        if (!fp) {
            std::perror("Failed to open /proc/self/maps");
            return entries;
        }

        char line[256];
        while (std::fgets(line, sizeof(line), fp)) {
            MemoryMapEntry entry;
            char offset[16], dev[16], inode[16], path[128];
            
            if (std::sscanf(line, "%" PRIx64 "-%" PRIx64 " %4s %15s %15s %15s %127s",
                           &entry.start_addr, &entry.end_addr,
                           entry.permissions, offset, dev, inode, path) >= 6) {
                
                if (std::strcmp(path, "[heap]") == 0) {
                    entry.region_type = "[heap]";
                } else if (std::strcmp(path, "[stack]") == 0) {
                    entry.region_type = "[stack]";
                } else {
                    entry.region_type = path;
                }

                entries.push_back(entry);
            }
        }

        std::fclose(fp);
        return entries;
    }

    // 模板函数：判断任意地址所属的内存区域
    template <typename T>
    static MemRegion getMemoryRegion(const T* addr) {
        if (addr == nullptr) {
            return MemRegion::Unknown;
        }

        const uint64_t target_addr = reinterpret_cast<uint64_t>(addr);
        const auto entries = parseMemoryMaps();
        if (entries.empty()) {
            return MemRegion::Unknown;
        }

        for (const auto& entry : entries) {
            if (target_addr >= entry.start_addr && target_addr < entry.end_addr) {
                // 优先判断堆/栈
                if (entry.region_type == "[heap]") {
                    return MemRegion::Heap;
                } else if (entry.region_type == "[stack]") {
                    return MemRegion::Stack;
                }

                // 按权限判断其他区域
                if (entry.permissions[0] == 'r' && entry.permissions[1] == '-' && entry.permissions[2] == 'x') {
                    return MemRegion::Text;       // 代码段（r-x）
                } else if (entry.permissions[0] == 'r' && entry.permissions[1] == '-' && entry.permissions[2] == '-') {
                    return MemRegion::RoData;     // 只读数据段（r--）
                } else if (entry.permissions[0] == 'r' && entry.permissions[1] == 'w' && entry.permissions[2] == '-') {
                    // .data 和 .bss 均为 rw-，此处简化：若需区分可扩展逻辑
                    return MemRegion::Data;       // 数据段（rw-）
                }
            }
        }

        return MemRegion::Unknown;
    }

    // 辅助函数：将枚举转为可读字符串（用于调试输出）
    static std::string getRegionName(MemRegion region) {
        switch (region) {
            case MemRegion::Text:    return "Text (代码段)";
            case MemRegion::RoData:  return "RoData (只读数据段)";
            case MemRegion::Data:    return "Data (数据段)";
            case MemRegion::Bss:     return "Bss (未初始化数据段)";
            case MemRegion::Stack:   return "Stack (栈)";
            case MemRegion::Heap:    return "Heap (堆)";
            case MemRegion::Unknown: return "Unknown (未知区域)";
            default:                 return "Invalid";
        }
    }
};

// 简化接口：适配原测试代码的 get_memory_region 函数名
template <typename T>
MemRegion get_memory_region(const T* addr) {
    return RegionDetector::getMemoryRegion(addr);
}

