#ifndef SUPER_EDA_LINKED_LIST_H
#define SUPER_EDA_LINKED_LIST_H

#include "../supermarket/sector.h"

namespace linked_list {
    namespace sectors {
        void insert(Sector *&list, Sector *&data);
        unsigned int length(Sector *&list);
    }
}

#endif //SUPER_EDA_LINKED_LIST_H
