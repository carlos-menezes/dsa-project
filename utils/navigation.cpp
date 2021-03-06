#include "navigation.h"
#include "io.h"
#include "array.h"

namespace navigation {
    void addItem(Navigation &navigation, Navigation::Item &item) {
        navigation.items[navigation.itemsAmount] = item;
        navigation.itemsAmount++;
    }

    void print(Navigation &navigation) {
        char title[1024];
        snprintf(title, sizeof title, "...: %s :...", navigation.title.c_str());
        io::output::divider(true);
        io::output::custom(io::BOLDCYAN, true, title);
        for (int i = 0; i < navigation.itemsAmount; ++i) {
            char idx[3];
            snprintf(idx, sizeof idx, "%d", i+1);
            io::output::custom(io::BOLDYELLOW, true,  idx, navigation.items[i].title);
        }
    }

    namespace management {
        Navigation buildNavigation(Supermarket &supermarket) {
            Navigation navigation {};
            navigation.itemsAmount = 0;
            navigation.title = "MANAGEMENT";
            navigation.items = new Navigation::Item[navigation::management::MAX_MANAGEMENT_ITEMS];

            auto removeProduct = Navigation::Item {
                    "Remove product",
                    [&supermarket] {
                        std::string productName;
                        io::input::getString(productName, "Product name > ");
                        if (!metadata::isValidProduct(supermarket, productName)) io::output::error("Product not found");
                        else supermarket::removeProducts(supermarket, productName);
                    }
            };
            navigation::addItem(navigation, removeProduct);

            auto updatePrice = Navigation::Item {
                "Update price",
                [&supermarket] {
                    std::string productName;
                    io::input::getString(productName, "Product name > ");

                    int newPrice;
                    try {
                        io::input::getInt(newPrice, "New price > ");
                    } catch (std::invalid_argument& ex) {
                        io::output::error("Invalid input value. Please, try again.");
                        return;
                    }

                    if (newPrice < 1 || newPrice > 80) {
                        io::output::error("Invalid price range (1-80EUR).");
                        return;
                    }

                    if (!metadata::isValidProduct(supermarket, productName)) io::output::error("Product not found in storage or invalid name");
                    else supermarket::updateProductsPrice(supermarket, productName, newPrice);
                }
            };
            navigation::addItem(navigation, updatePrice);

            auto startCampaign = Navigation::Item {
                    "Start campaign",
                    [&supermarket] {
                        std::string area;
                        io::input::getString(area, "Area > ");

                        int discount;
                        try {
                            io::input::getInt(discount, "Discount (1-99 %) > ");
                        } catch (std::invalid_argument& ex) {
                            io::output::error("Invalid input value. Please, try again.");
                            return;
                        }

                        if (discount <= 0 || discount >= 100) {
                            printf("\033[31m[ERROR]\033[0m Invalid discount. Must be in range 1%%-99%%.\n");
                            return;
                        }

                        int duration;
                        try {
                            io::input::getInt(duration, "Duration > ");
                        } catch (std::invalid_argument& ex) {
                            io::output::error("Invalid input value. Please, try again.");
                            return;
                        }

                        if (!supermarket::areaExists(supermarket, area)) io::output::error("Area not found");
                        else supermarket::startDiscount(supermarket, area, discount, duration);
                    }
            };
            navigation::addItem(navigation, startCampaign);

            auto saveState = Navigation::Item {
                    "Save state",
                    [&supermarket] {
                        std::string fileName = supermarket::saveState(supermarket);
                        io::output::info("State saved in file `%s`", fileName.c_str());
                    }
            };
            navigation::addItem(navigation, saveState);

            auto loadState = Navigation::Item {
                    "Load state",
                    [&supermarket] {
                        std::string path;
                        io::input::getString(path, "Path > ");
                        try {
                            supermarket = supermarket::loadState(path);
                            io::output::info("Supermarket loaded from file `%s`", path.c_str());
                        } catch (std::invalid_argument &e) {
                            io::output::error(e.what());
                        }
                    }
            };
            navigation::addItem(navigation, loadState);

            auto printProducts = Navigation::Item {
                    "Print products",
                    [&supermarket] {
                        char option;
                        io::input::getChar(option, "Select an option: (a)lphabetic | (p)rice > ");
                        if (option != 'a' && option != 'p') {
                            io::output::error("Invalid input option. Please, try again.");
                            return;
                        }

                        // Create a temporary array which holds products both in a) storage and b) each sector
                        const unsigned int maxProducts = 15 * 12 + supermarket::MAX_STORAGE;
                        unsigned int count = 0;
                        auto *products = new Product[maxProducts];
                        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
                            Sector &sector = supermarket.sectors[i];
                            for (int j = 0; j < sector.productsAmount; ++j) {
                                products[count] = sector.products[j];
                                count++;
                            }
                        }

                        for (int i = 0; i < supermarket.storageAmount; ++i) {
                            products[count] = supermarket.storage[i];
                            count++;
                        }

                        if (option == 'a') {
                            array::sortByName(products, maxProducts);
                        } else {
                            array::sortByPrice(products, maxProducts);
                        }

                        for (int i = 0; i < maxProducts; ++i) {
                            product::printData(products[i]);
                        }
                    }
            };
            navigation::addItem(navigation, printProducts);

            auto createArea = Navigation::Item {
                    "Create area",
                    [&supermarket] {
                        std::string area;
                        io::input::getString(area, "Name > ");
                        if (supermarket::areaExists(supermarket, area)) io::output::error("Area already exists");
                        else metadata::addArea(supermarket, area);
                    }
            };
            navigation::addItem(navigation, createArea);

            auto showSales = Navigation::Item {
                    "Show sales",
                    [&supermarket] {
                        std::string owner;
                        io::input::getString(owner, "Owner > ");
                        int count = 0;
                        if (!supermarket::isValidOwner(supermarket, owner)) io::output::error("Owner not found");
                        else {
                            for (int i = 0; i < supermarket.sectorsAmount; ++i) {
                                Sector &sector = supermarket.sectors[i];
                                if (sector.owner != owner) continue;
                                for (int j = 0; j < sector.salesAmount; ++j) {
                                    sale::printData(sector.sales[j]);
                                    count++;
                                }
                            }
                            if (count == 0) io::output::info("Owner `%s` hasn't made any sales", owner.c_str());
                            else io::output::info("Owner `%s` has made %d sales", owner.c_str(), count);
                        }

                    }
            };
            navigation::addItem(navigation, showSales);

            auto changeArea = Navigation::Item {
                    "Change area",
                    [&supermarket]() {
                        char id;
                        io::input::getChar(id, "Sector ID > ");
                        /**
                         * Sectors ID start at char 65, 'A'.
                         * Subtracting an integer from a character returns a new integer.
                         * If ID 'A' is inserted, idAsIndex = 65 - 65 = 0, thus we can access the first element of the
                         * sectors array which has ID A.
                         */
                        int idAsIndex = id - 65;
                        if (idAsIndex < 0 || idAsIndex > supermarket.sectorsAmount) {
                            io::output::error("Invalid sector `%c`", id);
                            return;
                        }

                        std::string area;
                        io::input::getString(area, "Area name > ");
                        if (!metadata::isValidArea(supermarket, area)) io::output::error("Area not found");
                        else {
                            Sector& sector = supermarket.sectors[idAsIndex];
                            sector.area = area;
                            sector.productsAmount = 0;
                            sector.products = new Product[sector.capacity];
                            io::output::info("Sector `%c` emptied and changed area to `%s`", sector.id, area.c_str());
                        }
                    }
            };
            navigation::addItem(navigation, changeArea);

            auto printSectors = Navigation::Item {
                    "Print sectors data",
                    [&supermarket] {
                        for (int i = 0; i < supermarket.sectorsAmount; ++i) {
                            sector::printData(supermarket.sectors[i]);
                        }
                    }
            };
            navigation::addItem(navigation, printSectors);

            auto printStorage = Navigation::Item {
                    "Print storage data",
                    [&supermarket] {
                        for (int i = 0; i < supermarket.storageAmount; ++i) {
                            product::printData(supermarket.storage[i]);
                        }
                    }
            };
            navigation::addItem(navigation, printStorage);

            return navigation;
        }

        void getInput(int& destination) {
            while (true) {
                io::output::divider(true);
                try {
                    char buffer[1024];
                    snprintf(buffer, sizeof buffer, "Select an option (1-%d) > ", navigation::management::MAX_MANAGEMENT_ITEMS);
                    io::input::getInt(destination, buffer);
                    if (destination >= 0 && destination <= management::MAX_MANAGEMENT_ITEMS) break;
                    io::output::error("Invalid input range. Please, try again.");
                } catch (std::invalid_argument& ex) {
                    io::output::error("Invalid input value. Please, try again.");
                }
            }
        }

        void process(Navigation& navigation) {
            navigation::print(navigation);
            io::output::custom(io::BOLDYELLOW, true, "0", "Return");
            int input;
            management::getInput(input);
            // If option is 0 ("Go back"), return the function and go back to the main display
            if (input == 0) return;
            navigation.items[input - 1].handler();
        }
    }

    namespace main {
        void getInput(char& destination) {
            while (true) {
                try {
                    io::output::divider(true);
                    io::input::getChar(destination, "Select an option: (n)ext - (m)anagement > ");
                    if (destination == 'n' || destination == 'm') break;
                    io::output::error("Invalid input key. Please, try again.");
                } catch (std::invalid_argument& ex) {
                    io::output::error("Invalid input value. Please, try again.");
                }

            }
        }
    }
}

