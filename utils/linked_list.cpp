//
// Created by Carlos on 18/05/2021.
//

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
    }
}
