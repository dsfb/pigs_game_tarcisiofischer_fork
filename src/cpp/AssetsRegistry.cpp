#include <AssetsRegistry.hpp>

void AssetsRegistry::load(SDL_Renderer* renderer)
{
    this->tileset = load_sprite("tiles.png", renderer);
    this->lifebar = load_sprite("lifebar.png", renderer);
    this->lifebar_heart = load_sprite("small_heart18x14.png", renderer);
    this->monogram = load_sprite("monogram.png", renderer);
    this->talk_baloon = load_sprite("talk_baloon.png", renderer);
    this->forest_background = load_sprite("forest_background.png", renderer);
}

AssetsRegistry::~AssetsRegistry()
{
    SDL_DestroyTexture(this->tileset);
    SDL_DestroyTexture(this->lifebar);
    SDL_DestroyTexture(this->lifebar_heart);
    SDL_DestroyTexture(this->monogram);
    SDL_DestroyTexture(this->talk_baloon);
    SDL_DestroyTexture(this->forest_background);
}

AssetsRegistry assets_registry;
