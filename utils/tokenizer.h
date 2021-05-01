//
// Created by Carlos on 01/05/2021.
//

#ifndef SUPER_EDA_TOKENIZER_H
#define SUPER_EDA_TOKENIZER_H

#include <string>

namespace tokenizer {
    const int MAX_ITEMS = 1024;

    std::string *split(const std::string &str, char c);
}

#endif //SUPER_EDA_TOKENIZER_H
