cmake_minimum_required(VERSION 4.4)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 20)
add_executable(FlappyBird src/main.cpp
        src/Application.cpp
        src/Application.h
        src/LTexture.cpp
        src/LTexture.h
        src/Random.cpp
        src/Random.h
        src/Bird.cpp
        src/Bird.h
        src/Vector.h
        src/GameConstants.h
        src/Pipe.cpp
        src/Pipe.h
        src/ManagePipes.cpp
        src/ManagePipes.h
)



find_package(SDL2 REQUIRED)
target_link_libraries(FlappyBird PRIVATE SDL2::SDL2main SDL2::SDL2)
find_package(SDL2_image REQUIRED CONFIG)
target_link_libraries(FlappyBird PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
find_package(SDL2_ttf REQUIRED CONFIG)
target_link_libraries(FlappyBird PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
find_package(SDL2_mixer REQUIRED CONFIG)
target_link_libraries(FlappyBird PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer)