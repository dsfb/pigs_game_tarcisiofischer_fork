#ifndef __SDL_WRAPPERS_HPP
#define __SDL_WRAPPERS_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

SDL_Texture* load_sprite(std::string const& filename, SDL_Renderer* renderer);
SDL_Texture* load_map_editor_sprite(std::string const& filename, SDL_Renderer* renderer);
fs::path get_assets_directory();
fs::path get_maps_directory();

struct SDL_Handler
{
    SDL_Handler();
    ~SDL_Handler();
};

#endif
