#include "BG_MAIN_INCLUDES.h";

#include "OrderPool.h"
#include "PriceLevel.h"

int main(){
    OrderPool<Order, 100000> orderPool;
    OrderPool<PriceLevel, 10000> levelPool;

    OrderBook book{};

    std::cout << "Starting Limit_Order_Book" << std::endl;



    return 0;
}
