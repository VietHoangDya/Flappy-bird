

#pragma once
#include <memory>
#include <SDL_events.h>
#include <vector>

#include "LTexture.h"
#include "Pipe.h"
#include "Vector.h"


class Bird
{
public:
    Bird();
    bool handleEvent(SDL_Event& e);
    void update();
    void loadBirdTexture(SDL_Renderer* renderer, const std::string_view birdTextures[]);
    void render(SDL_Renderer* renderer);
    SDL_FRect getFRect();
    bool checkCollision(LTexture& base);
    bool checkCollision(std::vector<std::unique_ptr<Pipe>>& pipes);
    bool checkCollision(SDL_FRect rect1, SDL_FRect rect2);
    float getPosX();

private:
    const float MAX_BIRD_VEL = 250.0;
    const float MAX_FALL_VEL = 1000.0;
    const float ACCELERATION = 750.0 ;
    const float MIN_BIRD_ANGLE = -30 ;
    const float MAX_BIRD_ANGLE = 90;
    const int ACTION_TIME = 250;
    LTexture mBirdTexture[3];
    float mBirdVel;
    Vector mBirdPos;
    float mBirdWidth;
    float mBirdHeight;
    float mBirdAngle;
    bool isAlive = true;
};
