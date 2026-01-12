export module Order;

export {
    enum TypeOrder{
        BUY,
        SELL
    };

    struct Order{
        Order ( uint64_t price, uint64_t orderId, uint64_t quantity, TypeOrder side) : price(price),
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
        
        uint64_t getTotalVolume(){
            return price * orderId;
        }

        bool buyOrder(){
            return side == TypeOrder::BUY;
        }
    };
}


}
