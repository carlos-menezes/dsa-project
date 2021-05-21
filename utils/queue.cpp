#include "queue.h"

namespace queue {
    void enqueue(Product *&queue, Product *&data) {
        auto *productCopy = new Product(*data);
        productCopy->next = nullptr;
        if (queue == nullptr) {
            queue = productCopy;
        } else {
            Product *it = queue;
            while (it->next != nullptr) {
                it = it->next;
            }
            it->next = productCopy;
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

    /*void dequeue(Product *&queue) {
        if (queue == nullptr) return;
        if (queue->next == nullptr) {
            queue = nullptr;
        } else {
            Product *temp = queue->next;
            delete queue;
            queue = temp;
        }
    }*/

    /*unsigned int length(Product *&queue) {
        const Product *aux = queue;
        unsigned int count = 0;
        while (aux->next != nullptr) {
            count++;
        }
        return count;
    }*/
}
