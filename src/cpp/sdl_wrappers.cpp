#include <sdl_wrappers.hpp>
#include <logging.hpp>

SDL_Texture* load_media(std::string const& filename, SDL_Renderer* renderer)
{
    auto* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        warn("Unable to load image. SDL Error: "s + SDL_GetError());
    }
    auto* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        warn("Unable to create texture from image. SDL Error: "s + SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
}

fs::path get_executable_directory()
{
    char* raw_base_path = SDL_GetBasePath();

    if (raw_base_path == nullptr) {
        warn("SDL_GetBasePath() failed: "s + SDL_GetError());
        return raw_base_path;
    }

    fs::path base_path(raw_base_path);
    SDL_free(raw_base_path);

    return base_path;
}

fs::path get_assets_directory()
{
    return get_executable_directory()
        / "assets";
}

fs::path get_maps_directory()
{
    return get_executable_directory()
        / "maps";
}

SDL_Texture* load_sprite(std::string const& filename, SDL_Renderer* renderer)
{
    fs::path sprite_path =
        get_assets_directory()
        / "sprites"
        / filename;

    return load_media(sprite_path.string(), renderer);
}

SDL_Texture* load_map_editor_sprite(std::string const& filename, SDL_Renderer* renderer)
{
    fs::path map_editor_sprite_path =
        get_assets_directory()
        / "map_editor"
        / filename;

    return load_media(map_editor_sprite_path.string(), renderer);
}

SDL_Handler::SDL_Handler()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        err("SDL could not be initialized! SDL Error: "s + SDL_GetError());
    }
    if (TTF_Init() != 0) {
        err("Failed to initialize TTF library");
    }
}

SDL_Handler::~SDL_Handler() {
    TTF_Quit();
    SDL_Quit();
}
