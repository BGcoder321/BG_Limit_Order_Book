#include "BG_MAIN_INCLUDES.h";

#include "ObjectPool.h"
#include "PriceLevel.h"
#include "OrderBook.h"
// constexpr size_t MAX_PRICE = static_cast<size_t>(1e5)+1;

int main(){
    ObjectPool<Order, MAX_PRICE> orderPool;
    ObjectPool<PriceLevel, MAX_PRICE> pricePool;

    OrderBook book(orderPool, pricePool);

    std::cout << "Starting Limit_Order_Book" << std::endl;



    return 0;
}
