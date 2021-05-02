#include <iostream>
#include <time.h>

#include "utils/runtime.h"

int main(int argc, char **argv) {
    srand(time(nullptr));

    if (argc == 1) return runtime::asNew();
    else if (argc == 2) return runtime::fromFile(argv[1]);
}
