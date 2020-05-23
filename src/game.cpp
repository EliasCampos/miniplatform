//
// Created by elias on 23.02.2020.
//

#include <string>
#include <SFML/Graphics.hpp>

#include "../includes/miniplatform/game.h"
#include "../includes/miniplatform/level.h"


GameInitializationException::GameInitializationException(std::string &reason): std::runtime_error(reason) {}


Game::Game()
{
    if (!font.loadFromFile("fonts/OpenSans-Bold.ttf"))
    {
        std::string error = "Can't initialize game: Failed to load font";
        throw GameInitializationException(error);
    }
    if (!music.openFromFile("music/soundtrack2.ogg"))
    {
        std::string error = "Can't initialize game: Failed to play music";
        throw GameInitializationException(error);
    }
    end_text = sf::Text("Congratulations, You Won!", font, 48);
    level_maps = Level::get_default_set();
    current_level_map = level_maps.begin();

    level.reset(*current_level_map);

    music.setLoop(true);
    music.play();
}

void Game::update_state(float time_frame) {
    if (current_level_map == level_maps.end())
    {
        return;
    }

    level.update(time_frame);
    if (!level.is_running())
    {
        if (level.is_completed())
        {
            ++current_level_map;
        }
        if (current_level_map != level_maps.end())
        {
            level.reset(*current_level_map);
        }
    }
}

void Game::render(sf::RenderWindow &window) {
    if (current_level_map != level_maps.end())
    {
        level.redraw(window);
    }
    else
    {
        draw_game_over(window);
    }
}
