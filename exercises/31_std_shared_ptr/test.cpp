#include<vector>
#include <memory>
#include<iostream>

int main(){


    auto shared = std::make_shared<int>(10);  // 第1行
    std::shared_ptr<int> ptrs[]{shared, shared, shared};
    std::weak_ptr<int> observer = shared;     // 第2行
    shared = observer.lock();                  // 第3行 
    std::cout<<observer.use_count()<<std::endl;

    return 0;
}