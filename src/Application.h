

#pragma once
#include <SDL_mixer.h>

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "Bird.h"
#include "ManagePipes.h"

enum class GameState
{
   GAME_READY, GAME_RUN ,GAME_OVER,
};

class Application
{
public:
    Application();
    ~Application();
    bool init();
    void loadMedia();
    void run();
    void close();
    Mix_Chunk* loadChunkAudio(const std::string& audioFile);
// ============================== RENDER OBJECT ==============================
    void renderPoints();
    void renderBase();
    void renderBackground();
// ============================== RENDER ALL ==============================
    void render();
// ============================== CALCULATE POINTS ==============================
    void calculatePoints();
private:
    const float MAX_PIXEL_SCROLLING = 125.0;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    //
    Bird mBird;
    LTexture mBase;
    LTexture mMessage;
    LTexture mGameOver;
    LTexture mBackground;
    LTexture mPoints[10];
    ManagePipes mManagePipes;
    Uint32 time;
    Uint32 currentTime;
    //
    GameState gameState = GameState::GAME_READY;
    Uint32 point = 0;
    //Audio
    Mix_Chunk* mWingSound = nullptr;
    Mix_Chunk* mPointSound = nullptr;
    Mix_Chunk* mDieSound = nullptr;
    Mix_Chunk* mHitSound = nullptr;
};
