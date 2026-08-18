//
// Created by pijay on 8/8/2026.
//

#include "ManagePipes.h"

#include <iostream>
#include <SDL_timer.h>

#include "GameConstants.h"
#include "Random.h"

ManagePipes::ManagePipes()
{
}

ManagePipes::~ManagePipes()
{
}

void ManagePipes::updatePipes(Uint32 deltaTime)
{
    lastSpawnTime +=deltaTime;
    for (int i = 0; i < pipes.size(); i++)
    {
        pipes[i]->update(deltaTime);
        if (pipes[i]->isOutScreen())
        {
            pipes.erase(pipes.begin() + i);
            --i;
        }
    }
    if (lastSpawnTime >= SPAWN_TIME)
    {
        pipes.emplace_back(std::make_unique<Pipe>(GameConstants::Specification::WINDOW_WIDTH,
            Random::randInt(150, GameConstants::Specification::WINDOW_HEIGHT - 100 - 112)));
        lastSpawnTime = 0;
    }
}

void ManagePipes::renderPipes(SDL_Renderer* renderer)
{
    for (auto& pipe : pipes)
    {
        pipe->render(renderer);
    }
}

std::vector<std::unique_ptr<Pipe>>& ManagePipes::getPipes()
{
    return pipes;
}



