#include "supermarket.h"
#include "../utils/random.h"
#include "sector.h"
#include "../utils/io.h"
#include "../utils/queue.h"


Sector *sector::create(Supermarket &supermarket) {
    auto *sector = new Sector;
    static char sectorID = 65;
    sector->id = sectorID;
    sector->capacity = random::i::inRange(5, 11);
    sector->area = supermarket.metadata.areas[random::i::inRange(0, 11)];

    /*char buffer[1024];
    snprintf(buffer, sizeof buffer, "Owner for sector %c > ", sector->id);
    io::input::getString(sector->owner, buffer);*/
    sector->owner = sectorID;
    sectorID++;
    sector->products = nullptr;
    sector->sales = nullptr;
    sector->salesAmount = 0;
    sector->discountDuration = 0;
    sector->discountValue = 0;

    sector->next = nullptr;
    return sector;
}

void sector::printData(Sector *sector) {
    char headline[1024];
    snprintf(headline, sizeof headline, "SECTOR: %c | AREA: %s | OWNER: %s | CAPACITY: %d | STOCK: %d", sector->id,
             sector->area.c_str(), sector->owner.c_str(), sector->capacity, queue::length(sector->products));
    io::output::custom(io::BOLDGREEN, true, headline);
    Product *product = sector->products;
    while (product != nullptr) {
        product::printData(product);
        product = product->next;
    }
}

Sector* sector::createFromString(std::string *str) {
    auto* sector = new Sector;
    sector->id = (str->c_str())[0];
    sector->owner = str[1];
    sector->area = str[2];
    sector->capacity = std::stoi(str[3]);
    sector->discountValue = std::stoi(str[5]);
    sector->discountDuration = std::stoi(str[6]);
    sector->products = nullptr;
    sector->sales = nullptr;
    sector->salesAmount = 0;
    sector->next = nullptr;
    return sector;
}
