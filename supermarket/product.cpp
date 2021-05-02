//
// Created by Carlos on 30/04/2021.
//

#include "supermarket.h"
#include "../utils/random.h"
#include "product.h"
#include "../utils/io.h"


Product product::create(Supermarket &supermarket) {
    Product product {};
    product.price = (double)random::i::inRangeEven(1, 80);
    /**
     * Every product is assigned an area. As products must be put into areas somewhen in the future, their areas must
     * be shared with, at least, one sector.
     */
     unsigned int randSector = random::i::inRange(0, supermarket.sectorsAmount - 1);
     product.area = supermarket.sectors[randSector].area;
     unsigned int randName = random::i::inRange(0, supermarket.metadata.namesAmount - 1);
     product.name = supermarket.metadata.names[randName];
     unsigned int randSupplier = random::i::inRange(0, supermarket.metadata.suppliersAmount - 1);
     product.supplier = supermarket.metadata.suppliers[randSupplier];
     return product;
}

void product::setPrice(Product &product, double price) {
    io::output::info("Product `%s` changed priced from %.2fEUR to %.2fEUR", product.name.c_str(), product.price, price);
    product.price = price;
}

void product::setInDiscount(Product &product, bool inDiscount) {
    product.inDiscount = inDiscount;
}

void product::printData(Product &product) {
    if (product.name.empty()) return;
    printf("NAME: %s | AREA: %s | SUPPLIER: %s | PRICE (EUR): %.2f | DISCOUNT: %s\n", product.name.c_str(), product.area.c_str(), product.supplier.c_str(), product.price, product.inDiscount ? "YES" : "NO");
}

Product product::createFromString(std::string *str) {
    Product product {};
    product.name = str[0];
    product.supplier = str[1];
    product.area = str[2];
    product.price = std::stof(str[3]);
    product.inDiscount = std::stoi(str[4]);
    return product;
}
