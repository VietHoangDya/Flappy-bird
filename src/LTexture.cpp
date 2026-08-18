//
// Created by pijay on 8/4/2026.
//

#include "LTexture.h"

#include <iostream>
#include <SDL_image.h>

LTexture::LTexture()
    : mTexture(nullptr), mWidth(0), mHeight(0)
{
}

LTexture::~LTexture()
{
    reset();
}

int LTexture::getWidth() const
{
    return mWidth;
}

int LTexture::getHeight() const
{
    return mHeight;
}

void LTexture::reset()
{
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

bool LTexture::loadImage(SDL_Renderer* renderer, const std::string& path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cout << "IMG_Load error: " << IMG_GetError() << "\n";
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (newTexture != nullptr)
        {
            mWidth = surface->w;
            mHeight = surface->h;
        }
        mTexture = newTexture;
        SDL_FreeSurface(surface);
    }
    return mTexture != nullptr;
}

void LTexture::render(SDL_Renderer* renderer, int x, int y, int width, int height,SDL_Rect* clip, double angle, SDL_Point* center,
    SDL_RendererFlip flip)
{
    SDL_Rect dest {x, y, mWidth, mHeight};
    if (width != 0)
    {
        dest.w = width;
    }
    if (height != 0)
    {
        dest.h = height;
    }
    if (clip != nullptr)
    {
        dest.w = clip->w;
        dest.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, mTexture, clip, &dest, angle, center, flip);
}
