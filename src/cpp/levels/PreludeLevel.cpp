#include <GameHandler.hpp>
#include <TransitionAnimation.hpp>
#include <characters/IGameCharacter.hpp>
#include <characters/Pig.hpp>
#include <characters/builder.hpp>
#include <io.hpp>
#include <levels/PreludeLevel.hpp>

PreludeLevel::PreludeLevel(GameHandler& game_handler)
    : map(load_map("maps/intro.map"))
    , characters(build_game_characters(game_handler.get_renderer(), map))
{
    prepare_script(this->characters, game_handler.get_transition_animation());
}

GameMap& PreludeLevel::get_map()
{
    return this->map;
}

std::vector<std::unique_ptr<IGameCharacter>>& PreludeLevel::get_characters()
{
    return this->characters;
}

std::function<void()> PreludeLevel::get_collision_callback(int callback_collision_id, IGameCharacter* character)
{
    return nullptr;
}

void prepare_script(std::vector<std::unique_ptr<IGameCharacter>>& game_characters, TransitionAnimation& transition_animation)
{
    auto pig1 = dynamic_cast<Pig*>(game_characters[0].get());
    auto pig2 = dynamic_cast<Pig*>(game_characters[1].get());
    auto pig3 = dynamic_cast<Pig*>(game_characters[2].get());

    auto pig1_color = RGBColor { 0, 100, 0 };
    auto pig2_color = RGBColor { 250, 50, 50 };
    auto pig3_color = RGBColor { 20, 30, 250 };

    transition_animation.register_transition_callback([&]() {
        // transition_animation.register_transition_callback(nullptr);
    });
    auto on_finish_animation = [&]() { transition_animation.reset(); };
}
