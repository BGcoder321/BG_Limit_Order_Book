#ifndef Order_H
#define Order_H
#include <cstdint>

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
                poolParent(nullptr) {} 

    uint64_t price;
    uint64_t orderId;
    uint64_t quantity;
    TypeOrder side;
    Order* prev;
    Order* next;
    Order* poolParent;
    
    inline constexpr uint64_t getNotional() noexcept { // should this be constexpr or const noexcept?
        return price * quantity;
    }

    inline constexpr bool buyOrder() noexcept{
        return side == TypeOrder::BUY;
    }
    
    constexpr void reset() noexcept{
        price = 0; 
        orderId = 0;
        quantity = 0;
        prev = nullptr;
        next = nullptr;
        poolParent = nullptr;
    }
};
#endif // Order_H