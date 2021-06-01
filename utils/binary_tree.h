#ifndef SUPER_EDA_BINARY_TREE_H
#define SUPER_EDA_BINARY_TREE_H

#include "../supermarket/sale.h"

namespace binary_tree {
    void insert(Sale *&tree, Sale *&sale);
    void traverse(Sale *&tree);
    void write(Sale *&tree, std::ofstream &out);

    unsigned int count(Sale *&tree);
}

#endif //SUPER_EDA_BINARY_TREE_H