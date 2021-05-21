#ifndef SUPER_EDA_NAVIGATION_H
#define SUPER_EDA_NAVIGATION_H

#include <string>
#include <functional>

struct Supermarket;

struct Navigation {
    struct Item {
        std::string title;
        std::function<void()> handler;
    };

    std::string title;
    Item* items;
    int itemsAmount;
};

namespace navigation {
    /**
     * Outputs the navigation to stdout.
     * @param navigation
     */
    void print(Navigation& navigation);

    /**
     * Adds an item to the navigation.
     * @param navigation
     * @param item
     */
    void addItem(Navigation &navigation, Navigation::Item& item);

    namespace management {
        const unsigned int MAX_MANAGEMENT_ITEMS = 10;

        /**
         * Gets input for processing action on the management menu.
         * User is prompted to enter a number between 0 and MAX_NAVIGATION_ITEMS.
         * @param destination
         */
        void getInput(int& destination);

        /**
         * Handles all the output/input process of the management navigation.
         * @param navigation
         */
        void process(Navigation& navigation);

        /**
         * Builds the management menu.
         * @param supermarket
         * @return
         */
        Navigation buildNavigation(Supermarket& supermarket);
    }

    namespace main {
        /**
         * Gets input for processing action on the main menu.
         * User is prompted to enter either `n` or `m`.
         * @param destination
         */
        void getInput(char& destination);
    }
}

#endif //SUPER_EDA_NAVIGATION_H
