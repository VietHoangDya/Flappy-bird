//
// Created by pijay on 8/4/2026.
//

#pragma once
#include <string>

namespace GameConstants
{
    namespace Specification
    {
        constexpr std::string_view TITLE = "Flappy Bird";
        constexpr int WINDOW_WIDTH = 576;
        constexpr int WINDOW_HEIGHT = 512;
        constexpr int SCREEN_FPS = 120;
        constexpr int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
    }

    namespace Texture
    {
        // BIRD IMAGE
        constexpr std::string_view YELLOW_BIRD[] = {
            "assets/sprites/yellowbird-downflap.png",
            "assets/sprites/yellowbird-midflap.png",
            "assets/sprites/yellowbird-upflap.png",
        };
        constexpr std::string_view RED_BIRD[] = {
            "assets/sprites/redbird-downflap.png",
            "assets/sprites/redbird-midflap.png",
            "assets/sprites/redbird-upflap.png",
        };
        constexpr std::string_view BLUE_BIRD[] = {
            "assets/sprites/bluebird-downflap.png",
            "assets/sprites/bluebird-midflap.png",
            "assets/sprites/bluebird-upflap.png",
        };
        // POINT
        constexpr std::string_view POINTS[]
        {
            "assets/sprites/0.png",
            "assets/sprites/1.png",
            "assets/sprites/2.png",
            "assets/sprites/3.png",
            "assets/sprites/4.png",
            "assets/sprites/5.png",
            "assets/sprites/6.png",
            "assets/sprites/7.png",
            "assets/sprites/8.png",
            "assets/sprites/9.png"
        };

    }
    namespace Audio
    {

    }
}
