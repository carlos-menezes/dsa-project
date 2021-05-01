//
// Created by Carlos on 30/04/2021.
//

#include "supermarket.h"
#include "../utils/io.h"

namespace sale {
    Sale create(Sector &sector, Product &product) {
        Sale sale {};
        sale.productName = product.name;
        sale.price = product.price;
        sale.sectorId = sector.id;
        return sale;
    }

    void printData(Sale &sale) {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "PRODUCT: %s | SECTOR: %c", sale.productName.c_str(), sale.sectorId);
        io::output::custom(io::BOLDGREEN, true, "SALE", buffer);
    }
}
