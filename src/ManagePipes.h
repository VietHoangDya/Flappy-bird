//
// Created by pijay on 8/8/2026.
//

#pragma once
#include <memory>
#include <vector>

#include "Pipe.h"
#include "Bird.h"

class ManagePipes
{
public:
    ManagePipes();
    ~ManagePipes();
    void updatePipes(Uint32 deltaTime);
    void renderPipes(SDL_Renderer* renderer);
    std::vector<std::unique_ptr<Pipe>>& getPipes();
private:
    std::vector<std::unique_ptr<Pipe>> pipes;
    const Uint32 SPAWN_TIME = 1500;
    Uint32 lastSpawnTime = 0;
};
