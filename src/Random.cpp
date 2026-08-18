

#include "Random.h"

std::mt19937 Random::mt(std::chrono::system_clock::now().time_since_epoch().count());

int Random::randInt(int min, int max)
{
    return min + mt() % (max - min + 1);
}
