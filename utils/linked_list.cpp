#include "linked_list.h"

namespace linked_list {
    namespace sectors {
        void insert(Sector *&list, Sector *&data) {
            auto *sectorCopy = new Sector(*data);
            if (list == nullptr) {
                sectorCopy->next = list;
                list = sectorCopy;
            } else {
                Sector *aux = list;
                while (aux != nullptr && aux->next != nullptr) {
                    aux = aux->next;
                }
                aux->next = sectorCopy;
                sectorCopy->next = nullptr;
            }
        }

        unsigned int length(Sector *&list) {
            unsigned int count = 0;
            for (Sector *sector = list; sector != nullptr; sector = sector->next) {
                count++;
            }
            return count;
        }
    }
}
