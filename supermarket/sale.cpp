#include "supermarket.h"
#include "../utils/io.h"
#include "sale.h"


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

    Sale createFromString(std::string *str) {
        Sale s;
        s.sectorId = (str->c_str())[0];
        s.productName = str[1];
        s.price = std::stod(str[2]);
        return s;
    }
}
