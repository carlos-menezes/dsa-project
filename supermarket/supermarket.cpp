#include <chrono>
#include <fstream>
#include "supermarket.h"
#include "../utils/random.h"
#include "../utils/io.h"
#include "../utils/tokenizer.h"
#include "../utils/queue.h"
#include "../utils/linked_list.h"

namespace supermarket {

    Supermarket supermarket::create() {
        Supermarket supermarket{};
        supermarket.iterations = 0;

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
        supermarket.sectors = nullptr;
        io::output::info("Initializing sectors");
        for (int i = 0; i < numSectors; ++i) {
            Sector *sector = sector::create(supermarket);
            linked_list::sectors::insert(supermarket.sectors, sector);
            delete sector;
        }

        /**
         * Initialize the storage.
         * The storage holds products. Initially, 50 products are placed in the storage.
         */
        supermarket.storage = nullptr;
        for (int i = 0; i < 50; ++i) {
            Product *product = product::create(supermarket);
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "NAME: %s | AREA: %s | PRICE: %.0fEUR", product->name.c_str(),
                     product->area.c_str(), product->price);
            io::output::custom(io::BOLDMAGENTA, true, "STORAGE ENTRY", buffer);
            queue::enqueue(supermarket.storage, product);
            supermarket.storageAmount++;
            delete product;
        }

        return supermarket;
    }
    
    void sellProducts(Supermarket &supermarket) {
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            Product *product = sector->products;
            while (product != nullptr) {
                unsigned int chance = random::i::inRange(1, 4);
                if (chance > 1) product = product->next;
                else {
                    Product *temp = product->next;
                    // TODO: create sale
                    char buffer[1024];
                    snprintf(buffer, sizeof buffer, "PRODUCT: %s | SECTOR: %c | PRICE (EUR): %.0f",
                             product->name.c_str(),
                             sector->id,
                             product->price);
                    io::output::custom(io::BOLDGREEN, true, "SALE", buffer);
                    queue::remove(sector->products, product);
                    sector->productsAmount--;
                    product = temp;
                }
            }
            sector = sector->next;
        }
        io::output::divider();
    }
    
    void restockStorage(Supermarket &supermarket) {
        for (int i = 0; i < MAX_STOCK_PER_ITER; ++i) {
            Product *product = product::create(supermarket);
            queue::enqueue(supermarket.storage, product);
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "NAME: %s | AREA: %s | PRICE: %.0fEUR", product->name.c_str(),
                     product->area.c_str(), product->price);
            io::output::custom(io::BOLDMAGENTA, true, "STORAGE RESTOCK", buffer);
            supermarket.storageAmount++;
            delete product;
        }
        io::output::divider();
    }
    
    void restockSectors(Supermarket &supermarket) {
        unsigned int stockedProducts = 0;
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            if (stockedProducts == MAX_STOCK_PER_ITER) break;
            else if (sector->productsAmount == sector->capacity) sector = sector->next;
            else {
                Product *product = supermarket.storage;
                while (product != nullptr) {
                    if (stockedProducts == MAX_STOCK_PER_ITER) break;
                    else if (sector->productsAmount == sector->capacity) break;
                    else if (product->area != sector->area) product = product->next;
                    else {
                        Product *temp = product->next;
                        queue::enqueue(sector->products, product);
                        sector->productsAmount++;
                        char buffer[1024];
                        snprintf(buffer, sizeof buffer, "PRODUCT: %s | SUPPLIER: %s | SECTOR: %c | PRICE: %.0fEUR",
                                 product->name.c_str(), product->supplier.c_str(), sector->id, product->price);
                        io::output::custom(io::BOLDYELLOW, true, "STOCK", buffer);
                        queue::remove(supermarket.storage, product);
                        supermarket.storageAmount--;
                        stockedProducts++;
                        product = temp;
                    }
                }
            }
            sector = sector->next;
        }
    }

    void verifyDiscounts(Supermarket &supermarket) {
        // TODO: implement
    }
    
    void updateProductsPrice(Supermarket &supermarket, const std::string &productName, double price) {
        unsigned int count = 0;
        // TODO: implement
        io::output::info("%d products had their price updated", count);
    }
    
    void removeProducts(Supermarket &supermarket, const std::string &productName) {
        int count = 0;
        // TODO: implement
        io::output::info("Removed %d instances of product `%s`", count, productName.c_str());
    }
    
    void printData(Supermarket &supermarket) {
        io::output::divider();
        char headline[1024];
        snprintf(headline, sizeof headline, "SUPER EDA | SECTORS: %d | STORAGE STOCK: %d", supermarket.sectorsAmount,
                 supermarket.storageAmount);
        io::output::custom(io::BOLDCYAN, true, headline);
        io::output::divider();
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            sector::printData(sector);
            sector = sector->next;
        }
    }
    
    bool areaExists(Supermarket &supermarket, const std::string &area) {
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
        // TODO: implement
        io::output::info("Started %d%% discount for %d days in area `%s`", discount, duration, area.c_str());
    }

    std::string saveState(Supermarket &supermarket) {
        char *fileName = new char[26];
        const char *lineBreak = "\n";
        auto sec_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        sprintf(fileName, "supermarket_%lld.txt", sec_since_epoch);

        std::ofstream fileBuffer(fileName);

        char *supermarketInfo = new char[8];
        sprintf(supermarketInfo, "%d|\n", supermarket.sectorsAmount);
        fileBuffer.write(supermarketInfo, strlen(supermarketInfo));
        delete[] supermarketInfo;

        for (int i = 0; i < supermarket.storageAmount; ++i) {
            Product &product = supermarket.storage[i];
            char *product_info = new char[1024];
            sprintf(product_info, "%s;%s;%s;%.0f;%d|", product.name.c_str(), product.supplier.c_str(),
                    product.area.c_str(), product.price, product.inDiscount);
            fileBuffer.write(product_info, strlen(product_info));
            delete[] product_info;
        }

        fileBuffer.write(lineBreak, strlen(lineBreak));

        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector &sector = supermarket.sectors[i];
            char *sector_info = new char[1024];
            sprintf(sector_info, "%c;%s;%s;%d;%u;%u;%u|", sector.id, sector.owner.c_str(), sector.area.c_str(),
                    sector.capacity, sector.productsAmount, sector.discountValue, sector.discountDuration);
            fileBuffer.write(sector_info, strlen(sector_info));
            delete[] sector_info;

            for (int j = 0; j < sector.productsAmount; ++j) {
                Product &product = sector.products[j];
                char *product_info = new char[1024];
                sprintf(product_info, "%s;%s;%s;%.0f;%d|", product.name.c_str(), product.supplier.c_str(),
                        product.area.c_str(), product.price, product.inDiscount);
                fileBuffer.write(product_info, strlen(product_info));
                delete[] product_info;
            }

            fileBuffer.write(lineBreak, strlen(lineBreak));
        }

        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            Sector &sector = supermarket.sectors[i];
            for (int j = 0; j < sector.salesAmount; ++j) {
                Sale &sale = sector.sales[j];
                char *sale_info = new char[1024];
                sprintf(sale_info, "%c;%s;%f|", sale.sectorId, sale.productName.c_str(), sale.price);
                fileBuffer.write(sale_info, strlen(sale_info));
                delete[] sale_info;
            }
        }

        fileBuffer.close();

        return fileName;
    }

    Supermarket loadState(const std::string &path) {
        std::ifstream fileBuffer(path);

        if (!fileBuffer.good()) {
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "Could not open file `%s`", path.c_str());
            throw std::invalid_argument(buffer);
        }

        Supermarket supermarket {};
        supermarket.metadata = metadata::load();
        supermarket.storage = new Product[MAX_STORAGE];
        supermarket.storageAmount = 0;

        /**
         * Load supermarket info, namely:
         * 1. amount of sectors
         */
        std::string supermarketInfo;
        std::getline(fileBuffer, supermarketInfo);
        auto *supermarketData = tokenizer::split(supermarketInfo, ';');
        supermarket.sectorsAmount = std::stoi(supermarketData[0]);
        supermarket.sectors = new Sector[supermarket.sectorsAmount];
        delete[] supermarketData;

        /**
         * Load storage info
         */
        std::string storageInfo;
        std::getline(fileBuffer, storageInfo);
        auto *storageData = tokenizer::split(storageInfo, '|');
        for (int i = 0; i < tokenizer::MAX_ITEMS; ++i) {
            if (storageData[i].length() == 0) break;
            auto *productInfo = tokenizer::split(storageData[i], ';');
            supermarket.storage[i] = product::createFromString(productInfo);
            delete[] productInfo;
            supermarket.storageAmount++;
        }
        delete[] storageData;

        /**
         * Load sectors
         */
        std::string sectorInfo;
        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
            std::getline(fileBuffer, sectorInfo);
            auto *sectorData = tokenizer::split(sectorInfo, '|');

            /**
             * Initialize each sector
             */
            auto *metadata = tokenizer::split(sectorData[0], ';');
            Sector &sector = supermarket.sectors[i];
            sector = sector::createFromString(metadata);
            delete[] metadata;

            /**
             * Import each product for the sector
             */
            for (int j = 1; j < sector.productsAmount + 1; ++j) {
                /*if (sectorData[j].length() == 0) break;*/
                auto *productInfo = tokenizer::split(sectorData[j], ';');
                sector.products[j-1] = product::createFromString(productInfo);
            }
        }

        /**
         * Lastly, load sales
         */
        std::string salesInfo;
        std::getline(fileBuffer, salesInfo);
        auto *salesData = tokenizer::split(salesInfo, '|');
        for (int i = 0; i < tokenizer::MAX_ITEMS; ++i) {
            if (salesData[i].length() == 0) break;
            auto *saleInfo = tokenizer::split(salesData[i], ';');
            int sectorId = saleInfo->at(0) - 65;
            Sector &sector = supermarket.sectors[sectorId];
            sector.sales[sector.salesAmount] = sale::createFromString(saleInfo);
            sector.salesAmount++;
            delete[] saleInfo;
        }
        delete[] salesData;

        return supermarket;
    }

    void process(Supermarket &supermarket) {
        supermarket::sellProducts(supermarket);
        supermarket::restockStorage(supermarket);
        supermarket::restockSectors(supermarket);
        supermarket::verifyDiscounts(supermarket);
        supermarket::printData(supermarket);
        Product *product = supermarket.storage;
        while (product != nullptr) {
            product::printData(product);
            product = product->next;
        }
    }
}

