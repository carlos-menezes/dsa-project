#include "tokenizer.h"

namespace tokenizer {
    std::string *split(const std::string &str, const char delim) {
        auto *tokens = new std::string[MAX_ITEMS];
        std::string acc;
        int idx = 0;
        for (char i : str) {
            if (i == delim) {
                tokens[idx] = acc;
                acc = "";
                idx++;
            } else {
                acc += i;
            }
        }
        tokens[idx] = acc;
        return tokens;
    }
}