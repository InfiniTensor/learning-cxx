#include"../exercise.h"
#include<iostream>
#include<thread>
#include<atomic>
#include<vector>
// 详细用法可参考 https://en.cppreference.com/w/cpp/atomic/atomic/
// https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange

struct Node {
    int value;
    Node* next;
};

// TODO: 将list_head改为原子指针
Node* list_head = nullptr;

void insert(int val) {
    // TODO: 将插入操作改为使用CAS实现无锁插入
    Node* new_node = new Node{val, nullptr};
    Node* old_head = list_head;
    new_node->next = old_head;
    list_head = new_node;
}


// ---- 不要修改以下代码 ----
int main() {
    const int num_threads = 30;
    const int inserts_per_thread = 1000;
    std::vector<std::thread> threads;

    // 启动多个线程进行插入操作
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([i, inserts_per_thread]() {
            for (int j = 0; j < inserts_per_thread; ++j) {
                insert(i * inserts_per_thread + j);
            }
        });
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 验证链表内容
    int count = 0;
    Node* current = list_head.load();
    while (current) {
        count++;
        current = current->next;
    }

    ASSERT(count == num_threads * inserts_per_thread,
           "链表中的节点数应等于插入的总节点数");

    return 0;
}