//
// Created by pijay on 8/8/2026.
//

#pragma once
#include "LTexture.h"
#include "Vector.h"


class Pipe
{
public:
    Pipe(float posX, float posY) ;
    ~Pipe() ;
    static void loadPipeTextures(SDL_Renderer* renderer, const std::string path);
    void render(SDL_Renderer* renderer);
    void update(Uint32 deltaTime);
    SDL_FRect getBottomRect();
    SDL_FRect getTopRect();
    void setPosY(float y);
    float getPosX();
    float getWidth();
    bool getIsPassed();
    void setIsPassed(bool value);
    bool isOutScreen() ;
private:
    const float MAX_PIPE_VEL = 125.0;
    static LTexture mPipe;
    Vector mPipePos ;
    SDL_Rect bottomPipe;
    SDL_Rect topPipe;
    bool isPassed = false;
};
