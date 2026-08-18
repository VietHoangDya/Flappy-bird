//
// Created by pijay on 8/8/2026.
//

#include "Pipe.h"

#include <iostream>
#include <SDL_timer.h>

#include "GameConstants.h"
LTexture Pipe::mPipe;
Pipe::Pipe(float posX, float posY)
    : mPipePos(posX,posY)
{
    bottomPipe.x = posX;
    bottomPipe.y = posY;
    bottomPipe.w = 52;
    bottomPipe.h = 320;
    topPipe.x = posX;
    topPipe.y = bottomPipe.y - 100 - 320;
    topPipe.w = 52;
    topPipe.h = 320;
}

Pipe::~Pipe()
{
}

void Pipe::loadPipeTextures(SDL_Renderer* renderer, const std::string path)
{
    mPipe.loadImage(renderer, path);
}

void Pipe::render(SDL_Renderer* renderer)
{
    mPipe.render(renderer,topPipe.x, topPipe.y, 0, 0,nullptr, 180.0);
    mPipe.render(renderer,bottomPipe.x, bottomPipe.y);
}

void Pipe::update(Uint32 deltaTime)
{
    mPipePos.x -= deltaTime/1000.0 * MAX_PIPE_VEL;
    topPipe.x = bottomPipe.x =mPipePos.x;

}

SDL_FRect Pipe::getBottomRect()
{
    return {(float)bottomPipe.x, (float)bottomPipe.y, (float)bottomPipe.w, (float)bottomPipe.h};
}

SDL_FRect Pipe::getTopRect()
{
    return {(float)topPipe.x, (float)topPipe.y, (float)topPipe.w, (float)topPipe.h};
}

void Pipe::setPosY(float y)
{
    mPipePos.y = y;

}

float Pipe::getPosX()
{
    return mPipePos.x;
}

float Pipe::getWidth()
{
    return mPipe.getWidth();
}

bool Pipe::getIsPassed()
{
    return isPassed;
}

void Pipe::setIsPassed(bool value)
{
    isPassed = value;
}

bool Pipe::isOutScreen()
{
    if (mPipePos.x + mPipe.getWidth() < 0) return true;
    else return false;
}

