#ifndef SUPER_EDA_SECTOR_H
#define SUPER_EDA_SECTOR_H

#include <string>
#include "supermarket.h"

struct Sector {
    char id;
    unsigned int capacity;
    std::string owner;
    std::string area;
    Product *products;
    Sale *sales;
    unsigned int discountDuration;
    unsigned int discountValue;
    Sector *next;
};

namespace sector {
    /**
     * Initializes a new sector.
     * @param supermarket
     * @return
     */
    Sector* create(Supermarket &supermarket);

    Sector* createFromString(std::string *str);

    void printData(Sector *sector);
}

#endif //SUPER_EDA_SECTOR_H
