//
// Created by Carlos on 30/04/2021.
//

#include "supermarket.h"
#include "../utils/random.h"
#include "sector.h"
#include "../utils/io.h"


Sector sector::create(Supermarket &supermarket) {
    Sector sector {};
    static char sectorID = 65;
    sector.id = sectorID; // TODO: change to `currentChar++`
    sector.capacity = random::i::inRange(5, 10);
    sector.area = supermarket.metadata.areas[random::i::inRange(0, 15)];
    sector.owner = sectorID; // TODO: get input
    sectorID++; // TODO: remove
    sector.products = new Product[sector.capacity];
    sector.sales = new Sale[sale::MAX_SALES];
    return sector;
}

void sector::addSale(Sector &sector, Sale &sale) {
    sector.sales[sector.salesAmount] = sale;
    sector.salesAmount++;
    sale::printData(sale);
}

void sector::addProduct(Sector &sector, Product &product) {
    sector.products[sector.productsAmount] = product;
    sector.productsAmount++;
    char buffer[1024];
    snprintf(buffer, sizeof buffer, "PRODUCT: %s | SECTOR: %c", product.name.c_str(), sector.id);
    io::output::custom(io::BOLDYELLOW, true, "STOCK", buffer);
}

void sector::decreaseDiscountDays(Sector &sector) {
    sector.discountDuration--;
}

void sector::setDiscountValue(Sector &sector, unsigned int discountValue) {
    sector.discountValue = discountValue;
}

void sector::printData(Sector& sector) {
    char headline[1024];
    snprintf(headline, sizeof headline, "SECTOR: %c | AREA: %s | OWNER: %s | CAPACITY: %d | STOCK: %d", sector.id, sector.area.c_str(), sector.owner.c_str(), sector.capacity, sector.productsAmount);
    io::output::custom(io::BOLDGREEN, true, headline);
    for (int i = 0; i < sector.productsAmount; ++i) {
        product::printData(sector.products[i]);
    }

}

Sector sector::createFromString(std::string *str) {
    Sector sector;
    sector.id = (str->c_str())[0];
    sector.owner = str[1];
    sector.area = str[2];
    sector.capacity = std::stoi(str[3]);
    sector.productsAmount = std::stoi(str[4]);
    sector.discountValue = std::stoi(str[5]);
    sector.discountDuration = std::stoi(str[6]);
    sector.products = new Product[sector.capacity];
    sector.sales = new Sale[sale::MAX_SALES];
    sector.salesAmount = 0;
    return sector;
}
