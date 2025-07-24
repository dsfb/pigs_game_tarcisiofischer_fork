#ifndef __IO_H
#define __IO_H

#include <GameMap.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sdl_wrappers.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void save_map(GameMap const& map, std::string const& filename);

GameMap load_map(std::string const& filename);

SDL_Texture* load_sprite(std::string const& filename, SDL_Renderer* renderer);

std::string get_full_music_file_path(std::string const& filename);

std::string get_full_sound_file_path(std::string const& filename);

#endif
