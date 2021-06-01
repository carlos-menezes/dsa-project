#include <chrono>
#include <fstream>
#include "supermarket.h"
#include "../utils/random.h"
#include "../utils/io.h"
#include "../utils/tokenizer.h"
#include "../utils/queue.h"
#include "../utils/linked_list.h"
#include "../utils/binary_tree.h"

namespace supermarket {

    Supermarket supermarket::create() {
        Supermarket supermarket{};

        /**
         * Load data from each of the files in the `files` directory into the supermarket.
         * These values are later retrieved when generating new sectors.
         */
        supermarket.metadata = metadata::load();
    
        /**
         * Initialize a random amount of sectors, each empty.
         */
        unsigned int numSectors = random::i::inRange(8, 12);
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
                    Sale *sale = sale::create(sector, product);
                    binary_tree::insert(sector->sales, sale);
                    sale::printData(sale);
                    queue::remove(sector->products, product);
                    sector->productsAmount--;
                    sector->salesAmount++;
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
            snprintf(buffer, sizeof buffer, "PRODUCT: %s | AREA: %s | PRICE: %.0fEUR", product->name.c_str(),
                     product->area.c_str(), product->price);
            io::output::custom(io::BOLDMAGENTA, true, "STORAGE RESTOCK", buffer);
            supermarket.storageAmount++;
            delete product;
        }
        io::output::divider();
    }

    void restockSectors(Supermarket &supermarket) {
        unsigned int stockedProducts = 0;
        Product *product = supermarket.storage;
        while (product != nullptr) {
            if (stockedProducts == MAX_STOCK_PER_ITER) break;
            Product *temp = product->next;
            Sector *sector = supermarket.sectors;
            while (sector != nullptr) {
                if (sector->area != product->area || sector->productsAmount == sector->capacity) sector = sector->next;
                else {
                    char buffer[1024];
                    snprintf(buffer, sizeof buffer, "PRODUCT: %s | AREA: %s | SECTOR: %c | PRICE: %.0fEUR",
                             product->name.c_str(), product->area.c_str(), sector->id, product->price);
                    io::output::custom(io::BOLDYELLOW, true, "STOCK", buffer);

                    queue::enqueue(sector->products, product);
                    queue::remove(supermarket.storage, product);
                    sector->productsAmount++;
                    supermarket.storageAmount--;
                    stockedProducts++;
                    break;
                }
            }
            product = temp;
        }
    }

    void verifyDiscounts(Supermarket &supermarket) {
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            if (sector->discountDuration > 0) {
                sector->discountDuration--;
                if (sector->discountDuration == 0) {
                    Product *product = sector->products;
                    while (product != nullptr) {
                        if (product->inDiscount) {
                            double originalPrice = (-100.0 * product->price) / (sector->discountValue - 100.0);
                            product::setPrice(product, originalPrice);
                            product::setInDiscount(product, false);
                        }
                        product = product->next;
                    }
                    io::output::info("Ended %d%% discount for sector `%c` (%s)", sector->discountValue, sector->id,
                                     sector->area.c_str());
                    sector->discountValue = 0;
                }
            }
            sector = sector->next;
        }
    }
    
    void updateProductsPrice(Supermarket &supermarket, const std::string &productName, double price) {
        unsigned int count = 0;
        Product *product = supermarket.storage;
        while (product != nullptr) {
            if (product->name == productName) {
                product::setPrice(product, price);
                count++;
            }
            product = product->next;
        }
        io::output::info("%d products had their price updated", count);
    }
    
    void removeProducts(Supermarket &supermarket, const std::string &productName) {
        int count = 0;
        // Remove products from storage
        Product *storageProduct = supermarket.storage;
        while (storageProduct != nullptr) {
            Product *temp = storageProduct->next;
            if (storageProduct->name == productName) {
                count++;
                io::output::info("Product `%s` removed from storage", storageProduct->name.c_str());
                queue::remove(supermarket.storage, storageProduct);
            }
            storageProduct = temp;
        }
        delete storageProduct;

        // Remove products from sectors
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            Product *sectorProduct = sector->products;
            while (sectorProduct != nullptr) {
                Product *temp = sectorProduct->next;
                if (sectorProduct->name == productName) {
                    count++;
                    io::output::info("Product `%s` removed from sector `%c`", sectorProduct->name.c_str(), sector->id);
                    queue::remove(sector->products, sectorProduct);
                }
                sectorProduct = temp;
            }
            sector = sector->next;
        }

        io::output::info("Removed %d instances of product `%s`", count, productName.c_str());
    }
    
    void printData(Supermarket &supermarket) {
        io::output::divider();
        char headline[1024];
        snprintf(headline, sizeof headline, "SUPER EDA | SECTORS: %d | STORAGE STOCK: %d",
                 linked_list::sectors::length(supermarket.sectors),
                 supermarket.storageAmount);
        io::output::custom(io::BOLDCYAN, true, headline);
        io::output::divider();
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            sector::printData(sector);
            sector = sector->next;
        }
    }

    bool isAreaInSectors(Supermarket &supermarket, const std::string &area) {
        bool found = false;
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            if (sector->area == area) {
                found = true;
                break;
            }
            sector = sector->next;
        }
        return found;
    }

    bool isValidOwner(Supermarket &supermarket, const std::string &owner) {
        bool found = false;
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            if (sector->owner == owner) {
                found = true;
                break;
            }
            sector = sector->next;
        }
        return found;
    }

    void
    startDiscount(Supermarket &supermarket, const std::string &area, unsigned int discount, unsigned int duration) {
        Sector *sector = supermarket.sectors;
        while (sector != nullptr) {
            if (sector->area != area) sector = sector->next;
            else {
                sector->discountValue = discount;
                sector->discountDuration = duration;
                Product *product = sector->products;
                while (product != nullptr) {
                    double newPrice = product->price - (product->price * (sector->discountValue / 100.0));
                    product::setPrice(product, newPrice);
                    product::setInDiscount(product, true);
                    product = product->next;
                }
                sector = sector->next;
            }
        }
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
        sprintf(supermarketInfo, "%d|\n", linked_list::sectors::length(supermarket.sectors));
        fileBuffer.write(supermarketInfo, strlen(supermarketInfo));
        delete[] supermarketInfo;

        for (Product* product = supermarket.storage; product != nullptr ; product = product->next){
            char *product_info = new char[1024];
            sprintf(product_info, "%s;%s;%s;%.0f;%d|", product->name.c_str(), product->supplier.c_str(),
                    product->area.c_str(), product->price, product->inDiscount);
            fileBuffer.write(product_info, strlen(product_info));
            delete[] product_info;
        }

        fileBuffer.write(lineBreak, strlen(lineBreak));

        for (Sector* sector = supermarket.sectors; sector != nullptr ; sector = sector->next) {
            char *sector_info = new char[1024];
            sprintf(sector_info, "%c;%s;%s;%d;%u;%u;%u|", sector->id, sector->owner.c_str(), sector->area.c_str(),
                    sector->capacity, sector->productsAmount, sector->discountValue, sector->discountDuration);
            fileBuffer.write(sector_info, strlen(sector_info));
            delete[] sector_info;

            for (Product* product = sector->products; product != nullptr ; product = product->next){
                char *product_info = new char[1024];
                sprintf(product_info, "%s;%s;%s;%.0f;%d|", product->name.c_str(), product->supplier.c_str(),
                        product->area.c_str(), product->price, product->inDiscount);
                fileBuffer.write(product_info, strlen(product_info));
                delete[] product_info;
            }

            fileBuffer.write(lineBreak, strlen(lineBreak));
        }

        for (Sector* sector = supermarket.sectors; sector != nullptr ; sector = sector->next) {
            binary_tree::write(sector->sales, fileBuffer);
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
        supermarket.storage = nullptr;
        supermarket.storageAmount = 0;

        /**
         * Load supermarket info, namely:
         * 1. amount of sectors
         */
        std::string supermarketInfo;
        std::getline(fileBuffer, supermarketInfo);
        auto *supermarketData = tokenizer::split(supermarketInfo, ';');
        int numSectors = std::stoi(supermarketData[0]);
        supermarket.sectors = nullptr;
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
            Product* product = product::createFromString(productInfo);
            queue::enqueue(supermarket.storage, product);
            delete[] productInfo;
            supermarket.storageAmount++;
        }
        delete[] storageData;

        /**
         * Load sectors
         */
        std::string sectorInfo;
        for (int i = 0; i < numSectors; ++i) {
            std::getline(fileBuffer, sectorInfo);
            auto *sectorData = tokenizer::split(sectorInfo, '|');

            /**
             * Initialize each sector
             */
            auto *metadata = tokenizer::split(sectorData[0], ';');
            Sector *sector = sector::createFromString(metadata);

            /**
             * Import each product for the sector
             */
            for (int j = 1; j < sector->productsAmount + 1; ++j) {
                auto *productInfo = tokenizer::split(sectorData[j], ';');
                Product* product = product::createFromString(productInfo);
                queue::enqueue(sector->products, product);
            }
            linked_list::sectors::insert(supermarket.sectors, sector);
            delete[] metadata;
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
            char sectorId = saleInfo->at(0);

            Sector *sector = supermarket.sectors;
            while (sector->id != sectorId) {
                sector = sector->next;
            }

            Sale *sale = sale::createFromString(saleInfo);
            binary_tree::insert(sector->sales, sale);
            sector->salesAmount++;
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
    }
}

