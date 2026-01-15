#ifndef OrderPool_H
#define OrderPool_H
#include "Order.h"
#include <vector>
#include <memory>

template <typename T, size_t maxPoolSize>
class OrderPool {
    OrderPool() : pool(maxPoolSize) {
        freeList.reserve(maxPoolSize);
        for(auto& order : pool){
            freeList.push_back(&order);
        }
    }

    [[nodiscard]] T* acquire(){ // nodiscard is cool cause apparently forces the compiler to ensure the result is used?!!
        if(freeList.empty()) return nullptr;
        T* avail = freeList.back();
        freeList.pop_back();
        return avail;
    }
    
    void release(T* ptr){
        ptr->reset();
        freeList.push_back(ptr);
    }
private:
    std::vector<T*> freeList;
    std::vector<T> pool;
};

#endif // OrderPool_H