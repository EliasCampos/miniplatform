//
// Created by elias on 22.02.2020.
//

#ifndef MINIPLATFORM_LEVEL_H
#define MINIPLATFORM_LEVEL_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "entities.h"


class Level
{

public:
    Level();

    void reset(std::vector<sf::String> &level_map);

    void update(float frame);

    void redraw(sf::RenderWindow &window);

    bool is_running();

    bool is_completed();

    static std::vector<std::vector<sf::String>> get_default_set();

private:
    sf::RectangleShape tile_rect = sf::RectangleShape((sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)));

    std::vector<sf::String> level_map;

    Player player  = Player(sf::Vector2f(100, 200));

    std::vector<Lava> lavas;
    std::vector<Coin> coins;

    void handle_keypress(float frame)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move_left(frame);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move_right(frame);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.jump();
        }
    }
};

#endif //MINIPLATFORM_LEVEL_H
