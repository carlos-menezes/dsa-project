//
// Created by Carlos on 30/04/2021.
//

#ifndef SUPER_EDA_PRODUCT_H
#define SUPER_EDA_PRODUCT_H

#include <string>
#include "supermarket.h"

struct Product {
    std::string name;
    std::string supplier;
    std::string area;
    double price;
    bool inDiscount;
};

namespace product {
    /**
     * Creates a new product with a random name retrieved from a list of names, a random price between 1 and 80 and
     * a random area.
     * @param supermarket supermarket which the generated product will be tied to
     * @return
     */
    Product create(Supermarket& supermarket);
    void setPrice(Product& product, double price);
    void setInDiscount(Product& product, bool inDiscount);
    void printData(Product& product);
}

#endif //SUPER_EDA_PRODUCT_H
