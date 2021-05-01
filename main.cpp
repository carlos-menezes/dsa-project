#include <iostream>
#include <time.h>

#include "utils/runtime.h"

int main() {
    srand (time(nullptr));
    return runtime::as_new();
}
