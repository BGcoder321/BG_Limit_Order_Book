#ifndef OrderBook_H
#define OrderBook_H
#include "ObjectPool.h"
#include "PriceLevel.h"

#include <cstdint>
#include <memory>
#include <array>

constexpr size_t MAX_PRICE = static_cast<size_t>(1e5)+1;

struct OrderBook{

    OrderBook(ObjectPool<Order, MAX_PRICE> orderPool,  
              OrderObjectPoolPool<Order, MAX_PRICE> pricePool) : 
                                                    orderPool_(orderPool), 
                                                    pricePool_(pricePool) {}

    void executeOrder(Order* order){

    }

    void cancelOrder(Order* order){
        auto relevantPriceLevel = static_cast<PriceLevel*>(order->parentLimit);
        if(!relevantPriceLevel) return;
        
        relevantPriceLevel->orderCount--;
        relevantPriceLevel->volume -= order->quantity;
        if(relevantPriceLevel->volume == 0){
            if(order->side == OrderType::BUY){
                bids[order->price] == nullptr;
                if(order->price == bestBid) updateBestBid();
            }else if(order->side == OrderType::SELL){
                asks[order->price] == nullptr;
                if(order->price == bestAsk) updateBestAsk();
            }
            pricePool_.release(relevantPriceLevel);
        }

        orderPool_.release(order);
    }

    void addOrder(Order* order){
        if(order->side == OrderType::BUY){
            if(bids[order->price] == nullptr){
                bids[order->price] = pricePool.acquire();
            }
            bids[order->price].update(order);
        }else if(order->side == OrderType::SELL){
            if(asks[order->price] == nullptr){
                asks[order->price] = pricePool.acquire();
            }
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

    void updateBestBid(){
        auto currBestBid = bestBid;
        while(currBestBid < MAX_PRICE && bids[currBestBid++] == nullptr);
        bestBid = currBestBid;
    }

    void updateBestAsk(){
        auto currBestAsk = bestAsk;
        while(currBestAsk > 0 && bids[currBestAsk--] == nullptr);
        bestAsk = currBestAsk;
    }


    std::array<PriceLevel*, MAX_PRICE> bids{};
    std::array<PriceLevel*, MAX_PRICE> asks{};
    uint64_t bestBid{0};
    uint64_t bestAsk{MAX_PRICE};
    ObjectPool<Order, MAX_PRICE> orderPool_;
    ObjectPool<PriceLevel, MAX_PRICE> pricePool_;
}

#endif // OrderBook_H