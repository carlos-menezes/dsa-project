#include "supermarket.h"
#include "../utils/io.h"

namespace sale {
    Sale *create(Sector *&sector, Product *&product) {
        auto *sale = new Sale;
        sale->productName = product->name;
        sale->price = product->price;
        sale->sectorId = sector->id;
        sale->right = nullptr;
        sale->left = nullptr;
        return sale;
    }

    void printData(Sale *&sale) {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "PRODUCT: %s | SECTOR: %c | PRICE (EUR): %.0f", sale->productName.c_str(),
                 sale->sectorId,
                 sale->price);
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
