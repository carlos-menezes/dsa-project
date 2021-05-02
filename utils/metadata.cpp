#include "metadata.h"
#include "files.h"
#include "io.h"
#include "../supermarket/supermarket.h"

namespace metadata {
    Metadata load() {
        Metadata metadata {};

        metadata.areasAmount = 0;
        metadata.areas = new std::string [MAX_AREAS];
        files::getFileLines(AREAS_FILE, metadata.areas, metadata.areasAmount);

        metadata.namesAmount = 0;
        metadata.names = new std::string [MAX_NAMES];
        files::getFileLines(NAMES_FILE, metadata.names, metadata.namesAmount);

        metadata.suppliersAmount = 0;
        metadata.suppliers = new std::string [MAX_SUPPLIERS];
        files::getFileLines(SUPPLIERS_FILE, metadata.suppliers, metadata.suppliersAmount);

        return metadata;
    }

    bool isValidProduct(Supermarket& supermarket, const std::string &entry) {
        bool found = false;
        for (int i = 0; i < supermarket.metadata.namesAmount; ++i) {
            if (supermarket.metadata.names[i].empty()) break;
            if (supermarket.metadata.names[i] == entry) {
                found = true;
                break;
            }
        }
        return found;
    }

    void addArea(Supermarket &supermarket, const std::string &area) {
        Metadata& metadata = supermarket.metadata;
        metadata.areas[metadata.areasAmount] = area;
        metadata.areasAmount++;
        io::output::info("Created new area `%s`", area.c_str());
    }

    bool isValidArea(Supermarket &supermarket, const std::string &area) {
        bool found = false;
        for (int i = 0; i < supermarket.metadata.areasAmount; ++i) {
            if (supermarket.metadata.areas[i] == area) {
                found = true;
                break;
            }
        }
        return found;
    }
}

