//
// Created by elias on 23.02.2020.
//

#ifndef MINIPLATFORM_GAME_H
#define MINIPLATFORM_GAME_H

#include <exception>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "level.h"


class GameInitializationException: std::runtime_error
{
public:
    explicit GameInitializationException(std::string &reason);
};


class Game
{
private:
    sf::Font font;
    sf::Text end_text;

    sf::Music music;

    std::vector<std::vector<sf::String>> level_maps;
    std::vector<std::vector<sf::String>>::iterator current_level_map;
    Level level;

    void draw_game_over(sf::RenderWindow &window)
    {
        sf::Vector2u wind_size = window.getSize();
        end_text.setFillColor(sf::Color(50, 200, 100));
        end_text.setPosition((float)(wind_size.x * 0.1), (float)(wind_size.y * 0.3));

        window.draw(end_text);
    }

public:
    Game();

    void update_state(float time_frame);

    void render(sf::RenderWindow &window);
};


#endif //MINIPLATFORM_GAME_H
