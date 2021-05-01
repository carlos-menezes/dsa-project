//
// Created by Carlos on 01/05/2021.
//

#include "array.h"

namespace array {
    void shiftLeft(Product* array, unsigned int size, unsigned int changed_index) {
        for (unsigned int i = changed_index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
    }

    void sortByName(Product *products, unsigned int size) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (products[j].name > products[j + 1].name) {
                    std::swap(products[j], products[j + 1]);
                }
            }
        }
    }

    void sortByPrice(Product *products, unsigned int size) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (products[j].price > products[j + 1].price) {
                    std::swap(products[j], products[j + 1]);
                }
            }
        }
    }
}

