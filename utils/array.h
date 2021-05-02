#ifndef SUPER_EDA_ARRAY_H
#define SUPER_EDA_ARRAY_H

#include "../supermarket/product.h"

namespace array {
    /**
     * Shifts an array to the left, filling void at array[changed_index] with array[changed_index+1]
     * @param array
     * @param size
     * @param changed_index
     */
    void shiftLeft(Product* array, unsigned int size, unsigned int changed_index);

    /**
     * Sorts an array of products by name in ascending order.
     * @param products
     * @param size
     */
    void sortByName(Product* products, unsigned int size);

    /**
     * Sorts an array of products by name in ascending price.
     * @param products
     * @param size
     */
    void sortByPrice(Product* products, unsigned int size);
}

#endif //SUPER_EDA_ARRAY_H
