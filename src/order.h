#include "BG_MAIN_INCLUDES.h";

enum TypeOrder{
    BUY,
    SELL
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
    
    inline constexpr uint64_t getTotalVolume(){
        return price * orderId;
    }

    inline constexpr bool buyOrder(){
        return side == TypeOrder::BUY;
    }
};