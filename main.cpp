#include <iostream>
#include <time.h>

#include "utils/runtime.h"
#include "utils/io.h"

int main(int argc, char **argv) {
    srand(time(nullptr));

    if (argc == 1) runtime::asNew();
    else if (argc == 2) runtime::fromFile(argv[1]);
    else io::output::info("USAGE: super_eda [file.txt]");
}
