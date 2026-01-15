#ifndef OrderBook_H
#define OrderBook_H
#include "PriceLevel.h"

#include <cstdint>
#include <memory>
#include <array>

constexpr size_t MAX_PRICE = static_cast<size_t>(1e5)+1;

struct OrderBook{

    OrderBook() {}

    void executeOrder(Order* order){}

    void cancelOrder(Order* order){}

    void addOrder(Order* order){
        if(order->side == OrderType::BUY){
            if(bids[order->price]){
                bids[order->price]{};
            }
            bids[order->price].update(order);
        }else if(order->side == OrderType::SELL){
            asks[order->price].update(order);
        }
    }

    PriceLevel* getPriceLevel(uint64_t price, OrderType side){
        if(side == OrderType::BUY){
            return bids[price];
        }else if(side == OrderType::SELL){
            return asks[price];
        }
    }

    std::array<PriceLevel*, MAX_PRICE> bids{};
    std::array<PriceLevel*, MAX_PRICE> asks{};
    uint64_t bestBid{0};
    uint64_t bestAsk{MAX_PRICE};
}

#endif // OrderBook_H