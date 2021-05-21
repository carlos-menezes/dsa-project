#include "binary_tree.h"
#include "../supermarket/sale.h"

namespace binary_tree {
    void insert(Sale *&tree, Sale *&sale) {
        if (tree == nullptr) {
            tree = sale;
        } else {
            if (sale->price > tree->price) insert(tree->right, sale);
            else insert(tree->left, sale);
        }
    }

    void traverse(Sale *&tree) {
        if (tree == nullptr) return;
        traverse(tree->left);
        sale::printData(tree);
        traverse(tree->right);
    }
}
