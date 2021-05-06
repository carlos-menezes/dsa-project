#include "files.h"

void files::getFileLines(const std::string &path, std::string *destination, unsigned int& size) {
    std::ifstream fileBuffer(path);

    if (!fileBuffer.good()) {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "Could not open file `%s`", path.c_str());
        throw std::invalid_argument(buffer);
    }

    std::string temp;
    while (std::getline(fileBuffer, temp)) {
        destination[size] = temp;
        size++;
    }
}