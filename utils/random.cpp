#include "random.h"
#include <random>

unsigned int randgen::i::inRangeEven(unsigned int min, unsigned int max) {
    return inRange(min, max / 2) * 2;
}

unsigned int randgen::i::inRange(unsigned int min, unsigned int max) {
    return min + (rand() % (max - min));
}
