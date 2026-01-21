#ifndef Order_H
#define Order_H
#include <cstdint>
#include "PriceLevel.h"

enum TypeOrder : uint8_t {
    BUY = 0,
    SELL = 1
};

struct alignas(64) Order{
    Order ( uint64_t price, uint64_t orderId, uint64_t quantity, TypeOrder orderType) : price(price),
                orderId(orderId),
                quantity(quantity),
                side(orderType),
                prev(nullptr),
                next(nullptr),
                parentLimit(nullptr) {} 
    Order() = default;

    uint64_t price;
    uint64_t orderId;
    uint64_t quantity;
    TypeOrder side;
    Order* prev;
    Order* next;
    PriceLevel* parentLimit;
    
    inline constexpr uint64_t getNotional() noexcept { // should this be constexpr or const noexcept?
        return price * quantity;
    }

    inline constexpr bool buyOrder() noexcept{
        return side == TypeOrder::BUY;
    }
    
    inline constexpr void reset() noexcept{
        price = 0; 
        orderId = 0;
        quantity = 0;
        prev = nullptr;
        next = nullptr;
        parentLimit = nullptr;
    }

    bool operator ==(const Order* a){
        return orderId == a->orderId;
    }
};
#endif // Order_H