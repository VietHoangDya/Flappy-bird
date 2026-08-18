//
// Created by pijay on 8/4/2026.
//

#pragma once
#include <chrono>
#include <random>


class Random
{
private:
    static std::mt19937 mt;
public:
    static int randInt(int min, int max);
};
