//
// Created by pijay on 8/4/2026.
//

#include "Bird.h"

#include <SDL_timer.h>

#include "GameConstants.h"

Bird::Bird()
    : mBirdVel(0), mBirdPos(0,0), mBirdWidth(0), mBirdHeight(0), mBirdAngle(0)
{
}

bool Bird::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        mBirdVel = -MAX_BIRD_VEL;
        mBirdAngle = MIN_BIRD_ANGLE;
        return true;
    }
    return false;
}

void Bird::update()
{
    if (!isAlive)
    {
        return;
    }
    static Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    mBirdVel += ACCELERATION * (currentTime - lastUpdateTime)/1000.0;
    if (mBirdVel > MAX_FALL_VEL) mBirdVel = MAX_FALL_VEL;
    mBirdPos.y += mBirdVel * (currentTime - lastUpdateTime)/1000.0;

    if (mBirdPos.y > GameConstants::Specification::WINDOW_HEIGHT - mBirdHeight || mBirdPos.y <0)
        mBirdPos.y -= mBirdVel * (currentTime - lastUpdateTime)/1000.0;
    mBirdAngle += mBirdVel * (currentTime - lastUpdateTime)/1000.0;
    if (mBirdAngle < MIN_BIRD_ANGLE) mBirdAngle = MIN_BIRD_ANGLE;
    if (mBirdAngle > MAX_BIRD_ANGLE) mBirdAngle = MAX_BIRD_ANGLE;
    lastUpdateTime = currentTime;
}

void Bird::loadBirdTexture(SDL_Renderer* renderer, const std::string_view birdTextures[])
{
    for (int i = 0 ;i<3; ++i)
    {
        mBirdTexture[i].loadImage(renderer,birdTextures[i].data());
    }
    mBirdWidth = mBirdTexture[0].getWidth();
    mBirdHeight = mBirdTexture[0].getHeight();
    mBirdPos.x = (GameConstants::Specification::WINDOW_WIDTH)/ 5;
    mBirdPos.y = (GameConstants::Specification::WINDOW_HEIGHT - mBirdHeight)/ 2;
}



void Bird::render(SDL_Renderer* renderer)
{
    static Uint32 changeActionTime = 0;
    static int action = 0;
    if (isAlive)
    {
        if ((SDL_GetTicks() - changeActionTime) >= ACTION_TIME)
        {
            changeActionTime = SDL_GetTicks();
            ++action;
        }
        if (action == 3) action = 0;
    }
    mBirdTexture[action].render(renderer,mBirdPos.x,mBirdPos.y, 0, 0,nullptr, mBirdAngle);
}

SDL_FRect Bird::getFRect()
{
    return {mBirdPos.x, mBirdPos.y, mBirdWidth, mBirdHeight};
}

bool Bird::checkCollision(LTexture& base)
{
    if (mBirdPos.y + mBirdWidth > GameConstants::Specification::WINDOW_HEIGHT - base.getHeight())
    {
        isAlive = false;
        return true;
    }
    return false;
}

bool Bird::checkCollision(std::vector<std::unique_ptr<Pipe>>& pipes)
{
    SDL_FRect birdRect = getFRect();
    for (auto& pipe : pipes)
    {
        SDL_FRect topPipe = pipe->getTopRect();
        SDL_FRect bottomPipe = pipe->getBottomRect();
        if (birdRect.x + birdRect.w < topPipe.x)
        {
            break;
        }
        if (checkCollision(topPipe,birdRect) || checkCollision(bottomPipe,birdRect)) return true;
    }
    return false;
}

bool Bird::checkCollision(SDL_FRect rect1, SDL_FRect rect2)
{
    if (rect1.x + rect1.w < rect2.x) return false;
    if (rect2.x + rect2.w < rect1.x) return false;
    if (rect1.y + rect1.h < rect2.y) return false;
    if (rect2.y + rect2.h < rect1.y) return false;
    return true;
}

float Bird::getPosX()
{
    return mBirdPos.x;
}
