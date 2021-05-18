#ifndef SUPER_EDA_QUEUE_H
#define SUPER_EDA_QUEUE_H

#include "../supermarket/product.h"

namespace queue {
    void enqueue(Product *&queue, Product *&element);

    void dequeue(Product *&queue);

    void remove(Product *&queue, Product *&element);

    unsigned int length(Product *&queue);
}

#endif //SUPER_EDA_QUEUE_H