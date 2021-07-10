#include "queue.h"

namespace queue {
    void enqueue(Product *&queue, Product *&element) {
        element->next = nullptr;
        if (queue == nullptr) {
            queue = element;
        } else {
            Product *it = queue;
            while (it->next != nullptr) {
                it = it->next;
            }
            it->next = element;
        }
    }

    void remove(Product *&queue, Product *&element) {
        if (queue == nullptr) return;
        Product *product = queue;
        if (element == queue) {
            queue = element->next;
            delete element;
        } else {
            while (product != nullptr && product->next != element) {
                product = product->next;
            }

            product->next = product->next->next;
            delete element;
        }
    }

    unsigned int length(Product *&queue) {
        unsigned int count = 0;
        for (Product *product = queue; product != nullptr; product = product->next) {
            count++;
        }
        return count;
    }
}