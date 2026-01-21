#ifndef PriceLevel_H
#define PriceLevel_H
#include "Order.h"

struct alignas(64) PriceLevel{
    uint64_t price{0};    
    uint64_t volume{0};    
    uint64_t orderCount{0};
    
    Order* head{nullptr};
    Order* tail{nullptr};

    void update(Order* order){
        orderCount++;
        volume += order->quantity;
        
        if(head == nullptr){
            head = order;
            tail = order;
        }else{
            order->prev = tail;
            tail->next = order;
            tail = tail->next;
        }
        order->parentLimit = this; 
    }

    void remove(Order* order){
        if(head == order){
            head = head->next;
            head->prev = nullptr;
        }else if(tail == order){
            tail = order->prev;
            tail->next = nullptr;
        }else{
            order->prev->next = order->next;
            order->next->prev = order->prev; 
        }
    }

    inline constexpr void reset() noexcept {
        price = 0;
        quantity = 0;
        orderCount = 0;
        head = nullptr;
        tail = nullptr;
    }
};

#endif // PriceLevel_H