#ifndef ORDER_H
#define ORDER_H
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
                next(nullptr) {} 

    uint64_t price;
    uint64_t orderId;
    uint64_t quantity;
    TypeOrder side;
    Order* prev;
    Order* next;
    
    inline constexpr uint64_t getTotalVolume() noexcept { // should this be constexpr or const noexcept?
        return price * quantity;
    }

    inline constexpr bool buyOrder(){
        return side == TypeOrder::BUY;
    }
};
#endif // ORDER_H