#include <AssetsRegistry.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__ || __MACH__
    #include <mach-o/dyld.h>
    #include <string>
#elif __linux__
    #include <unistd.h>
    #include <limits.h> // For PATH_MAX
#endif

std::string getInitialPath() {
    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, buffer, MAX_PATH);
        return buffer;
    #elif __APPLE__ || __MACH__
        uint32_t bufferSize = PATH_MAX;
        std::vector<char> buffer(bufferSize);
        if (_NSGetExecutablePath(buffer.data(), &bufferSize) == 0) {
            return buffer.data();
        } else {
            buffer.resize(bufferSize); // Resize if necessary
            _NSGetExecutablePath(buffer.data(), &bufferSize);
            return buffer.data();
        }
    #elif __linux__
        char buffer[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len != -1) {
            buffer[len] = '\0';
            return buffer;
        }
    #endif

    return ""; // Handle error
}


void AssetsRegistry::load(SDL_Renderer* renderer)
{
    std::string str_path = getInitialPath();

    fs::path initial_path(str_path);
    fs::path directory_path = initial_path.parent_path();

    fs::path assets_sprites_path = fs::path("assets") / fs::path("sprites");

    fs::path full_assets_sprites_path = directory_path / assets_sprites_path;

    std::cout << "Path of tiles.png: " << (full_assets_sprites_path / std::filesystem::path("tiles.png")).string() << std::endl;

    this->tileset = load_media((full_assets_sprites_path / std::filesystem::path("tiles.png")).string(), renderer);
    this->lifebar = load_media((full_assets_sprites_path / std::filesystem::path("lifebar.png")).string(), renderer);
    this->lifebar_heart = load_media((full_assets_sprites_path / std::filesystem::path("small_heart18x14.png")).string(), renderer);
    this->monogram = load_media((full_assets_sprites_path / std::filesystem::path("monogram.png")).string(), renderer);
    this->talk_baloon = load_media((full_assets_sprites_path / std::filesystem::path("talk_baloon.png")).string(), renderer);
    this->forest_background = load_media((full_assets_sprites_path / std::filesystem::path("forest_background.png")).string(), renderer);
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
