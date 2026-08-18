//
// Created by pijay on 8/3/2026.
//

#include "Application.h"
#include <format>
#include <iostream>
#include "GameConstants.h"
#include "Pipe.h"
Application::Application()
    : mWindow(nullptr), mRenderer(nullptr)
{
}


Application::~Application()
{
    close();
}

bool Application::init()
{
    if (SDL_Init((SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0))
    {
        // Khởi tạo SDL
        std::cout << "SDL could not initialize! SDL error: " << SDL_GetError() << "\n";
        return false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "SDL could not set hints! SDL Error: " << SDL_GetError() << "\n";
        }
        mWindow = SDL_CreateWindow(GameConstants::Specification::TITLE.data(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                    GameConstants::Specification::WINDOW_WIDTH, GameConstants::Specification::WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if (mWindow == nullptr)
        {
            std::cout << "Window creation failed! SDL Error: " << SDL_GetError() << "\n";
            return false;
        }
        else
        {
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (mRenderer == nullptr)
            {
                std::cout << "Renderer creation failed! SDL Error: " << SDL_GetError() << "\n";
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "IMG_Init failed! SDL_image Error: " << IMG_GetError() << "\n";
                    return false;
                }
                if (Mix_OpenAudio(44000, MIX_DEFAULT_FORMAT, 2,2048) < 0)
                {
                    std::cout << "Mix_OpenAudio failed! SDL Error: " << Mix_GetError() << "\n";
                }
            }
        }
    }
    return true;
}

void Application::loadMedia()
{
    // Texture
    mBird.loadBirdTexture(mRenderer, GameConstants::Texture::YELLOW_BIRD);
    mBase.loadImage(mRenderer, "assets/sprites/base.png");
    mMessage.loadImage(mRenderer, "assets/sprites/message.png");
    mGameOver.loadImage(mRenderer, "assets/sprites/gameover.png");
    mBackground.loadImage(mRenderer, "assets/sprites/background-day.png");
    Pipe::loadPipeTextures(mRenderer,"assets/sprites/pipe-green.png");
    for (int i =  0; i<=9; ++i)
    {
        mPoints[i].loadImage(mRenderer,GameConstants::Texture::POINTS[i].data());
    }
    // Audio
    mWingSound = loadChunkAudio("assets/audio/wing.wav");
    mPointSound = loadChunkAudio("assets/audio/point.wav");
    mDieSound = loadChunkAudio("assets/audio/die.wav");
    mHitSound = loadChunkAudio("assets/audio/hit.wav");
}

void Application::run()
{

    if (!init())
    {
        std::cout << "Failed to initialize! SDL Error: " << SDL_GetError() << "\n";
        return;
    }
    loadMedia();
    SDL_Event e;
    bool quit = false;
    time = SDL_GetTicks();
    while (!quit)
    {
        currentTime = SDL_GetTicks();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && gameState == GameState::GAME_READY) gameState = GameState::GAME_RUN;
            if (gameState == GameState::GAME_RUN)
            {
                if (mBird.handleEvent(e))
                {
                    Mix_PlayChannel(-1,mWingSound,0);
                }
            }
        }
        //
        switch (gameState)
        {
            case GameState::GAME_READY:
                {
                    break;
                }
            case GameState::GAME_RUN:
                {
                    calculatePoints();
                    mBird.update();
                    mManagePipes.updatePipes(currentTime - time);
                    if (mBird.checkCollision(mBase) || mBird.checkCollision(mManagePipes.getPipes()))
                    {
                        Mix_PlayChannel(-1,mHitSound,0);
                        Mix_PlayChannel(-1,mDieSound,0);
                        gameState = GameState::GAME_OVER;
                    }
                    break;
                }
            case GameState::GAME_OVER:
                {
                    if (!mBird.checkCollision(mBase))
                    {
                        mBird.update();
                    }
                }
        }
        render();
        time = currentTime;
    }
}

void Application::close()
{
    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Mix_Chunk* Application::loadChunkAudio(const std::string& audioFile)
{
    Mix_Chunk* chunk = Mix_LoadWAV(audioFile.c_str());
    if (chunk == nullptr)
    {
        std::cout << "Failed to load chunk audio! SDL_mix Error: " << Mix_GetError() << "\n";
    }
    return chunk;
}


// ============================== RENDER OBJECT ==============================
void Application::renderPoints()
{
    std::string strPoint = std::format("{}", point);
    int pointLength = strPoint.length();
    int widthRender =  pointLength * 24 ;
    int startXRender = (GameConstants::Specification::WINDOW_WIDTH - widthRender ) / 2;
    for (int i = 0 ;i<pointLength; i++)
    {
        mPoints[strPoint[i] - '0'].render(mRenderer, startXRender, 20);
        startXRender += 24 ;
    }
}

void Application::renderBase()
{
    static float scrollingOffset = 0 ;
    if (gameState == GameState::GAME_READY || gameState == GameState::GAME_RUN) scrollingOffset -= (currentTime - time)/1000.0 * MAX_PIXEL_SCROLLING;
    time = currentTime;
    if (scrollingOffset <= -mBase.getWidth())
    {
        scrollingOffset += mBase.getWidth();
    }
    int posX = scrollingOffset;
    int posY = GameConstants::Specification::WINDOW_HEIGHT - mBase.getHeight();
    while (posX < GameConstants::Specification::WINDOW_WIDTH)
    {
        mBase.render(mRenderer, posX, posY);
        posX += mBase.getWidth();
    }
}

void Application::renderBackground()
{
    int posX = 0;
    while (posX < GameConstants::Specification::WINDOW_WIDTH)
    {
        mBackground.render(mRenderer, posX, 0);
        posX += mBackground.getWidth();
    }
}

// ============================== RENDER ALL ==============================
void Application::render()
{
    SDL_RenderClear(mRenderer);
    renderBackground();
    mManagePipes.renderPipes(mRenderer);
    renderBase();
    mBird.render(mRenderer);
    if (gameState != GameState::GAME_READY)
    {
        renderPoints();
    }
    if (gameState == GameState::GAME_OVER)
    {
        mGameOver.render(mRenderer,( GameConstants::Specification::WINDOW_WIDTH - mGameOver.getWidth() ) / 2,
            ( GameConstants::Specification::WINDOW_HEIGHT - mGameOver.getHeight() ) / 2 );
    }
    if (gameState == GameState::GAME_READY)
    {
        mMessage.render(mRenderer,(GameConstants::Specification::WINDOW_WIDTH - mMessage.getWidth()) / 2,
            (GameConstants::Specification::WINDOW_HEIGHT - mMessage.getHeight()) / 2);
    }
    SDL_RenderPresent(mRenderer);
}

void Application::calculatePoints()
{
    auto& pipes = mManagePipes.getPipes();
    for (auto& pipe : pipes)
    {
        if (mBird.getPosX() > pipe->getPosX() + pipe->getWidth() && pipe->getIsPassed() == false)
        {
            pipe->setIsPassed(true);
            ++point;
            Mix_PlayChannel(-1,mPointSound,0);
        }
    }
}
