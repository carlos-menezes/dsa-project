#ifndef SUPER_EDA_SALE_H
#define SUPER_EDA_SALE_H

#include <string>
#include "supermarket.h"

struct Sale {
    std::string productName;
    double price;
    char sectorId;
    Sale *right;
    Sale *left;
};

namespace sale {
    const unsigned int MAX_SALES = 1024;

    Sale *create(Sector *&sector, Product *&product);

    Sale createFromString(std::string *str);

    void printData(Sale *&sale);
}

#endif //SUPER_EDA_SALE_H
