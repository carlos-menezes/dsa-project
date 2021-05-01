//
// Created by Carlos on 30/04/2021.
//

#ifndef SUPER_EDA_FILES_H
#define SUPER_EDA_FILES_H

#include <string>
#include <fstream>

namespace files {
    /**
     * Loads a specific file content in string array pointer `destination`
     * @param path file location
     * @param destination pointer to string array where the lines will be copied to
     * @param size size of the string array
     */
    void getFileLines(const std::string& path, std::string* destination, unsigned int& size);
}

#endif //SUPER_EDA_FILES_H
