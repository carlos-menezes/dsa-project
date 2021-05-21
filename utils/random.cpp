#include "random.h"
#include <random>

unsigned int random::i::inRangeEven(unsigned int min, unsigned int max) {
    return inRange(min, max / 2) * 2;
}

unsigned int random::i::inRange(unsigned int min, unsigned int max) {
    return min + (rand() % (max - min));
}