//
// Created by Carlos on 30/04/2021.
//

#include "supermarket.h"
#include "../utils/random.h"
#include "../utils/array.h"
#include "../utils/io.h"

namespace supermarket {
    
    Supermarket supermarket::create() {
        Supermarket supermarket {};
    
        /**
         * Load data from each of the files in the `files` directory into the supermarket.
         * These values are later retrieved when generating new sectors.
         */
        supermarket.metadata = metadata::load();
    
        /**
         * Initialize a random amount of sectors, each empty.
         */
        unsigned int numSectors = random::i::inRange(8, 12);
        supermarket.sectorsAmount = numSectors;
        supermarket.sectors = new Sector[numSectors];
        for (int i = 0; i < numSectors; ++i) {
            supermarket.sectors[i] = sector::create(supermarket);
        }
    
        /**
         * Initialize the storage.
         * The storage holds products. Initially, 50 products are placed in the storage.
         */
         supermarket.storage = new Product[MAX_STORAGE];
        for (int i = 0; i < 50; ++i) {
            supermarket.storage[i] = product::create(supermarket);
            supermarket.storageAmount++;
        }
    
        return supermarket;
    }
    
    void addToStorage(Supermarket &supermarket, Product &product) {
        supermarket.storage[supermarket.storageAmount] = product;
        supermarket.storageAmount++;
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "NAME: %s | AREA: %s | PRICE: %.2f€", product.name.c_str(), product.area.c_str(), product.price);
        io::output::custom(io::BOLDMAGENTA, true, "STORAGE", buffer);
    }
    
    void sellProducts(Supermarket &supermarket) {
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector& sector = supermarket.sectors[i];
            for (int j = 0; j < sector.productsAmount; ++j) {
                Product& product = sector.products[j];
                int chance = random::i::inRange(1, 4);
                if (chance > 1) continue;
                auto sale = sale::create(sector, product);
                sector::addSale(sector, sale);
                array::shiftLeft(sector.products, sector.productsAmount, j);
                sector.productsAmount--;
            }
        }

        io::output::divider();
    }
    
    void restockStorage(Supermarket &supermarket) {
        for (int i = 0; i < MAX_STOCK_PER_ITER; ++i) {
            Product product = product::create(supermarket);
            supermarket::addToStorage(supermarket, product);
        }
    
        io::output::divider();
    }
    
    void restockSectors(Supermarket &supermarket) {
        unsigned int stockedCount = 0;
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector& sector = supermarket.sectors[i];
            if (stockedCount == MAX_STOCK_PER_ITER) break;
            if (sector.productsAmount == sector.capacity) continue;
            for (int j = 0; j < supermarket.storageAmount; ++j) {
                Product& product = supermarket.storage[j];
                if (stockedCount == MAX_STOCK_PER_ITER) break;
                if (product.area != sector.area) continue;
                if (sector.productsAmount == sector.capacity) continue;
                sector::addProduct(sector, product);
                array::shiftLeft(supermarket.storage, supermarket.storageAmount, j);
                j--;
                supermarket.storageAmount--;
                stockedCount++;
            }
        }
    }
    
    void increaseIterations(Supermarket &supermarket) {
        supermarket.iterations++;
    }
    
    void verifyDiscounts(Supermarket &supermarket) {
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector& sector = supermarket.sectors[i];
            if (sector.discountDuration > 0) {
                sector::decreaseDiscountDays(sector);
                if (sector.discountDuration == 0) {
                    for (int j = 0; j < sector.productsAmount; ++j) {
                        Product& product = sector.products[j];
                        if (!product.inDiscount) continue;
                        double newPrice = (-100.0*product.price)/(sector.discountValue-100.0);
                        product::setPrice(product, newPrice);
                        product::setInDiscount(product, false);
                    }
                    sector::setDiscountValue(sector, 0);
                }
            }
        }
    }
    
    void updateProductsPrice(Supermarket &supermarket, const std::string &productName, double price) {
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector& sector = supermarket.sectors[i];
            for (int j = 0; j < sector.productsAmount; ++j) {
                Product& product = sector.products[j];
                if (productName == product.name) {
                    product::setPrice(product, price);
                }
            }
        }
    }
    
    void removeProducts(Supermarket &supermarket, const std::string &productName) {
        int count = 0;
        for (int i = 0; i < supermarket.storageAmount; ++i) {
            Product& product = supermarket.storage[i];
            if (productName == product.name) {
                count++;
                io::output::info("Product `%s` removed from storage", product.name.c_str());
                array::shiftLeft(supermarket.storage, supermarket.storageAmount, i);
                i--;
                supermarket.storageAmount--;
            }
        }
    
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector& sector = supermarket.sectors[i];
            for (int j = 0; j < sector.productsAmount; ++j) {
                Product &product = sector.products[j];
                if (productName == product.name) {
                    count++;
                    io::output::info("Product `%s` removed from sector `%c`", product.name.c_str(), sector.id);
                    array::shiftLeft(sector.products, sector.productsAmount, j);
                    j--;
                    sector.productsAmount--;
                }
            }
        }
    
        io::output::info("Removed %d instances of product `%s`", count, productName.c_str());
    }
    
    void printData(Supermarket &supermarket) {
        io::output::divider();
        char headline[1024];
        snprintf(headline, sizeof headline, "SUPER EDA | SECTORS: %d | STORAGE STOCK: %d", supermarket.sectorsAmount, supermarket.storageAmount);
        io::output::custom(io::BOLDCYAN, true, headline);
        io::output::divider();
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            sector::printData(supermarket.sectors[i]);
        }
    }
    
    bool isValidArea(Supermarket &supermarket, const std::string &area) {
        bool found = false;
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            if (supermarket.sectors[i].area == area) {
                found = true;
                break;
            }
        }
        return found;
    }

    bool isValidOwner(Supermarket &supermarket, const std::string &owner) {
        bool found = false;
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            if (supermarket.sectors[i].owner == owner) {
                found = true;
                break;
            }
        }
        return found;
    }

    void
    startDiscount(Supermarket &supermarket, const std::string &area, unsigned int discount, unsigned int duration) {
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector& sector = supermarket.sectors[i];
            if (area == sector.area) {
                sector.discountValue = discount;
                sector.discountDuration = duration;
                for (int j = 0; j < sector.productsAmount; ++j) {
                    Product& product = sector.products[j];
                    double newPrice = product.price - (product.price * (sector.discountValue / 100.0));
                    product::setPrice(product, newPrice);
                    product::setInDiscount(product, true);
                }
            }
        }

        io::output::info("Started %d%% discount for %d days in area `%s`", discount, duration, area.c_str());
    }

    void process(Supermarket &supermarket) {
        supermarket::sellProducts(supermarket);
        supermarket::restockStorage(supermarket);
        supermarket::restockSectors(supermarket);
        supermarket::increaseIterations(supermarket);
        supermarket::verifyDiscounts(supermarket);
        supermarket::printData(supermarket);
    }
}

