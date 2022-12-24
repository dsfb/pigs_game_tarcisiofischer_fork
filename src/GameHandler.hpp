#ifndef __GAME_HANDLER_HPP
#define __GAME_HANDLER_HPP

#include <StateTimeout.hpp>
#include <GameTimeHandler.hpp>
#include <Vector2D.hpp>
#include <levels/IGameLevel.hpp>
#include <memory>
#include <random.hpp>
#include <sdl_wrappers.hpp>
#include <screens/TitleScreen.hpp>
#include <TransitionAnimation.hpp>
#include <WindowShaker.hpp>

class SDL_Window;

class GameHandler {
public:
    GameHandler();
    ~GameHandler();

    void process_inputs();
    void update();
    void render();
    void delay();

    inline bool is_game_finished() const
    {
        return this->game_finished;
    }

    inline SDL_Renderer* get_renderer()
    {
        return this->renderer;
    }

    // TODO: const correctness
    inline TransitionAnimation& get_transition_animation()
    {
        return this->transition_animation;
    }

    // TODO: const correctness
    inline WindowShaker& get_window_shaker()
    {
        return this->window_shaker;
    }

    // TODO: Review this, check if really necessary workflow
    inline IScreen* get_active_screen()
    {
        return this->screen.get();
    }

    inline GameTimeHandler const& get_time_handler() const
    {
        return this->time_handler;
    }
private:
    static std::unique_ptr<TitleScreen> create_title_screen(GameHandler* game_handler);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameTimeHandler time_handler;
    bool game_finished;
    std::unique_ptr<IScreen> screen;
    WindowShaker window_shaker;
    TransitionAnimation transition_animation;
};

#endif
