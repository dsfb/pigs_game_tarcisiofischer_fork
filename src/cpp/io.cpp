#include <io.hpp>
#include <logging.hpp>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__ || __MACH__
#include <mach-o/dyld.h>
    #include <string>
#elif __linux__
    #include <unistd.h>
    #include <limits.h> // For PATH_MAX
#endif

void save_map(GameMap const& map, std::string const& filename)
{
    std::ofstream mapfile(filename, std::ios::binary | std::ios::out);
    if (!mapfile.is_open()) {
        err("Could not open file to write. filename="s + filename);
    }
    auto bin_write = [&mapfile](int const& data) { mapfile.write(reinterpret_cast<const char*>(&data), sizeof(int)); };

    bin_write(map.width);
    bin_write(map.height);
    for (int i = 0; i < map.height; ++i) {
        for (int j = 0; j < map.width; ++j) {
            bin_write(map.tilemap[i][j]);
        }
    }
    bin_write(map.interactables.size());
    for (auto const& interactable : map.interactables) {
        bin_write(interactable.position.x);
        bin_write(interactable.position.y);
        bin_write(interactable.id);
        bin_write(interactable.flip);
    }
    mapfile.close();
}

GameMap load_map(std::string const& filename)
{
    std::ifstream mapfile(filename, std::ios::binary | std::ios::in);
    if (!mapfile.is_open()) {
        err("Could not load file to read. filename="s + filename);
    }

    auto bin_read_nextint = [&mapfile](int& target) { mapfile.read(reinterpret_cast<char*>(&target), sizeof(int)); };

    auto map = GameMap { 0, 0 };

    bin_read_nextint(map.width);
    bin_read_nextint(map.height);

    map.tilemap = std::vector<std::vector<int>>(map.height, std::vector<int>(map.width));
    for (int i = 0; i < map.height; ++i) {
        for (int j = 0; j < map.width; ++j) {
            bin_read_nextint(map.tilemap[i][j]);
        }
    }

    int size = 0;
    bin_read_nextint(size);
    int position_x = 0;
    int position_y = 0;
    int id = 0;
    int flip = 0;
    for (int i = 0; i < size; ++i) {
        bin_read_nextint(position_x);
        bin_read_nextint(position_y);
        bin_read_nextint(id);
        bin_read_nextint(flip);
        map.interactables.push_back({ { position_x, position_y }, id, flip });
    }

    mapfile.close();

    return map;
}

std::string get_executable_game_path()
{
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

SDL_Texture* load_sprite(std::string const& filename, SDL_Renderer* renderer)
{
    std::string str_executable_game_path = get_executable_game_path();

    fs::path executable_game_path(str_executable_game_path);
    fs::path executable_game_directory_path = executable_game_path.parent_path();

    fs::path assets_sprites_path = fs::path("assets") / fs::path("sprites");

    fs::path full_assets_sprites_path = executable_game_directory_path / assets_sprites_path;

    return load_media((full_assets_sprites_path / std::filesystem::path(filename)).string(), renderer);
}

std::string get_full_music_file_path(std::string const& filename)
{
    std::string str_executable_game_path = get_executable_game_path();

    fs::path executable_game_path(str_executable_game_path);
    fs::path executable_game_directory_path = executable_game_path.parent_path();

    fs::path assets_music_path = fs::path("assets") / fs::path("music");

    fs::path full_assets_music_path = executable_game_directory_path / assets_music_path;

    return (full_assets_music_path / std::filesystem::path(filename)).string();
}

std::string get_full_sound_file_path(std::string const& filename)
{
    return get_full_music_file_path(filename);
}
