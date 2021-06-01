#ifndef SUPER_EDA_METADATA_H
#define SUPER_EDA_METADATA_H

#include <string>

struct Supermarket;

struct Metadata {
    unsigned int areasAmount;
    std::string *areas;
    unsigned int namesAmount;
    std::string *names;
    unsigned int suppliersAmount;
    std::string *suppliers;
    unsigned int runtimeAreasAmount;
    std::string *runtimeAreas;
};

namespace metadata {
    const int MAX_NAMES = 100;
    const int MAX_SUPPLIERS = 15;
    const int MAX_AREAS = 1024;

    #define NAMES_FILE "./files/names.txt"
    #define AREAS_FILE "./files/areas.txt"
    #define SUPPLIERS_FILE "./files/suppliers.txt"

    /**
     * Load data from datafiles
     * @return
     */
    Metadata load();

    /**
     * Checks whether a product name is valid (i.e. is included in `names.txt`)
     * @param supermarket
     * @param entry
     * @return
     */
    bool isValidProduct(Supermarket &supermarket, const std::string &entry);

    /**
     * Adds an area to the supermarket's metadata struct but not to the `areas.txt` file
     * @param supermarket
     * @param area
     */
    void addRuntimeArea(Supermarket &supermarket, const std::string &area);

    bool isAreaInRuntime(Supermarket &supermarket, const std::string &area);
}

#endif //SUPER_EDA_METADATA_H
