//
// Created by Carlos on 30/04/2021.
//

#include "files.h"

void files::getFileLines(const std::string &path, std::string *destination, unsigned int& size) {
    std::ifstream f(path);
    std::string temp;
    while (std::getline(f, temp)) {
        destination[size] = temp;
        size++;
    }
}