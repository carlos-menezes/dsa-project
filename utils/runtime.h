#ifndef SUPER_EDA_RUNTIME_H
#define SUPER_EDA_RUNTIME_H

namespace runtime {
    int fromFile(const std::string &path);

    [[noreturn]] int asNew();
}

#endif //SUPER_EDA_RUNTIME_H
