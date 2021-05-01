//
// Created by Carlos on 30/04/2021.
//

#include "random.h"
#include <random>

unsigned int random::i::inRangeEven(unsigned int min, unsigned int max) {
    return min + 2 * (rand() % (int) (max / 2));
}

unsigned int random::i::inRange(unsigned int min, unsigned int max) {
    return min + rand() % (max - min + 1);
}


