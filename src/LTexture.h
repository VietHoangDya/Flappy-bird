

#pragma once
#include <SDL_render.h>
#include <string>


class LTexture
{
public:
    LTexture();
    ~LTexture();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    void reset();
    bool loadImage(SDL_Renderer* renderer ,const std::string& path);
    void render(SDL_Renderer* renderer, int x, int y, int width = 0, int height = 0 ,SDL_Rect* clip = nullptr, double angle = 0.0,
                SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
