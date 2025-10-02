#pragma once
#include <SDL.h>
#include <map>

    static const std::map<SDL_Keycode, int> keyboard = {
    {SDLK_1, 0x1}, 
    {SDLK_2, 0x2}, 
    {SDLK_3, 0x3}, 
    {SDLK_4, 0xC}, 
    {SDLK_a, 0x4}, 
    {SDLK_z, 0x5}, 
    {SDLK_e, 0x6}, 
    {SDLK_r, 0xD}, 
    {SDLK_q, 0x7}, 
    {SDLK_s, 0x8}, 
    {SDLK_d, 0x9}, 
    {SDLK_f, 0xE}, 
    {SDLK_w, 0xA}, 
    {SDLK_x, 0x0}, 
    {SDLK_c, 0xB}, 
    {SDLK_v, 0xF}  
    };
