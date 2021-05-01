//
// Created by Carlos on 30/04/2021.
//

#ifndef SUPER_EDA_SUPERMARKET_H
#define SUPER_EDA_SUPERMARKET_H

#include "../utils/metadata.h"

struct Product;
struct Sector;
struct Sale;
struct Supermarket;

#include "product.h"
#include "sector.h"
#include "sale.h"

struct Supermarket {
    Sector* sectors;
    unsigned int sectorsAmount;

    Product* storage;
    unsigned int storageAmount;

    int iterations;

    Metadata metadata;
};

namespace supermarket {
    const unsigned int MAX_STOCK_PER_ITER = 10;
    const unsigned int MAX_STORAGE = 1024;
    const unsigned int MAX_SALES = 1024;

    /**
     * Initialize a supermarket.
     *
     * Every new supermarket is assigned a random number of sectors, each of the latter with a random area assigned to
     * it (retrieved from `areas.txt`).
     * @return empty supermarket
     */
    Supermarket create();

    /**
     * Processes a new cycle.
     * In any cycle, the following actions are taken:
     *  1. Every product is checked and sold if certain condition is met (view implementation)
     *  2. The supermarket's storage is refilled
     *  3. The supermarket's sectors are refilled
     *  4. Discounts are verified
     *  5. Data is outputted to the screen
     * @param supermarket
     */
    void process(Supermarket& supermarket);
    void sellProducts(Supermarket &supermarket);
    void restockStorage(Supermarket &supermarket);
    void restockSectors(Supermarket& supermarket);
    void addToStorage(Supermarket& supermarket, Product& product);
    void increaseIterations(Supermarket& supermarket);
    void verifyDiscounts(Supermarket& supermarket);
    void removeProducts(Supermarket& supermarket, const std::string& productName);
    void updateProductsPrice(Supermarket& supermarket, const std::string& productName, double price);
    void printData(Supermarket& supermarket);
    void startDiscount(Supermarket& supermarket, const std::string& area, unsigned int discount, unsigned int duration);
    bool areaExists(Supermarket& supermarket, const std::string& area);
    bool isValidOwner(Supermarket& supermarket, const std::string& owner);
    std::string saveState(Supermarket& supermarket);
    Supermarket loadState(const std::string& path);
}

#endif //SUPER_EDA_SUPERMARKET_H
