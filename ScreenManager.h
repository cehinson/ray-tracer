#pragma once

#include <SDL.h>
#include <cstdint>
#include "Core/Vec3.h"

namespace ch
{

struct sdl_error
{
};
inline void sdl_check(bool allclear)
{
    if (!allclear)
        throw sdl_error();
}

/**
* @brief Use RAII for SDL2
* 
*/
class ScreenManager
{
    // Screen size
    const size_t nr = 100;
    const size_t nc = 200;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screen;
    SDL_Texture *texture;

  public:
    ScreenManager();
    ~ScreenManager();
    void render();
    void save();
    void put_pixel(int x, int y, Vec3<> v);
};

} // namespace ch