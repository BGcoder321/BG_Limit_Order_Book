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
            tail->next = order;
            tail = tail->next;
        }
    }
};

#endif // PriceLevel_H