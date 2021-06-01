#include <fstream>
#include <iostream>
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

    void write(Sale *&tree, std::ofstream &out) {
        if (!tree) return;

        char *saleInfo = new char[1024];
        sprintf(saleInfo, "%c;%s;%f|", tree->sectorId, tree->productName.c_str(), tree->price);
        out.write(saleInfo, strlen(saleInfo));
        delete[] saleInfo;

        write(tree->left, out);
        write(tree->right, out);
    }

    unsigned int count(Sale *&tree) {
        unsigned int c = 1;
        if (tree == nullptr) return 0;
        else {
            c += count(tree->left);
            c += count(tree->right);
            return c;
        }
    }
}
