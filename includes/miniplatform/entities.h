//
// Created by elias on 22.02.2020.
//

#ifndef MINIPLATFORM_ENTITIES_H
#define MINIPLATFORM_ENTITIES_H

#include <random>

#include <SFML/Graphics.hpp>

#include "effect.h"
#include "settings.h"
#include "level_map.h"


class Entity
{
public:

    virtual void update(float frame, LevelMap &level_map) = 0;

    void render(sf::RenderWindow &window);

    sf::FloatRect get_rect();

    virtual void update_display(LevelMap &level_map);

protected:
    sf::FloatRect rect;
    sf::RectangleShape sprite;
    sf::Color base_color;

};

class Player: public Entity
{
public:
    explicit Player(sf::Vector2f init_pos);

    void update(float time, LevelMap &level) override;

    // Motion control:

    void move_left(float time);

    void move_right(float time);

    void jump();

    void touch_coin();

    // State control:

    void set_position(sf::Vector2f position);

    void set_dead();

    void set_won();

    // State info:
    sf::Vector2f get_offset();

    bool is_touches(Entity &entity);

    bool is_died();

    bool is_winner();

    // Display control
    void update_display(LevelMap &level_map) override;

private:
    static const unsigned int WIDTH = 16;
    static const unsigned int HEIGHT = 30;

    float dx, dy;
    bool is_on_ground;

    float player_step = 0.1;
    float gravity = 0.0005;
    float lim = 0.05;

    bool is_dead = false;
    bool is_won = false;
    float finalization_time = 3000;  // in microseconds

    void check_block_collision(LevelMap &level_map, unsigned int direction)
    {
        for (int i = ((int)rect.top / (int)BLOCK_SIZE); i <= ((int)(rect.top + HEIGHT) / (int)BLOCK_SIZE); i++)
        {
            sf::String line = level_map.getLine(i);
            for (int j = ((int)rect.left / (int)BLOCK_SIZE); j <= ((int)(rect.left + WIDTH) / (int)BLOCK_SIZE); j++)
            {
                char el = (char)line[j];
                if (el == '#')
                {
                    handle_wall_collision(direction, j, i);
                }
                else if (el == '+')
                {
                    set_dead();
                }
            }
        }
    }

    void handle_wall_collision(unsigned int direction, int horizontal_shift, int vertical_shift)
    {
        if (dx > 0 && direction == 0)
        {
            rect.left = (float)(horizontal_shift * BLOCK_SIZE) - WIDTH - lim;
        }
        if (dx < 0 && direction == 0)
        {
            rect.left = (float)((horizontal_shift + 1) * BLOCK_SIZE) + lim;
        }
        if (dy > 0 && direction == 1)
        {
            rect.top = (float)(vertical_shift * BLOCK_SIZE) - HEIGHT - lim;
            dy = 0;
            is_on_ground = true;
        }
        if (dy < 0 && direction == 1)
        {
            rect.top = (float)((vertical_shift + 1) * BLOCK_SIZE) + lim;
            dy = 0;
        }
    }
};

class Lava: public Entity
{
public:
    Lava(float init_x, float init_y, bool is_repeat, bool is_horizontal, int direction);

    void set_offset(sf::Vector2f player_offset);

    void update(float time, LevelMap &level) override;

private:
    float start_x, start_y;

    static const unsigned int WIDTH = (unsigned int)(BLOCK_SIZE * 0.99);
    static const unsigned int HEIGHT = (unsigned int)(BLOCK_SIZE * 0.99);

    float speed = 0.1;
    float lim = 0.05;
    bool is_vertical = false;
    bool is_reflected = false;
    sf::Vector2f offset;

    void check_block_collision(LevelMap &level_map)
    {
        for (int i = ((int)rect.top / (int)BLOCK_SIZE); i <= ((int)(rect.top + HEIGHT) / (int)BLOCK_SIZE); i++)
        {
            sf::String line = level_map.getLine(i);
            for (int j = ((int)rect.left / (int)BLOCK_SIZE); j <= ((int)(rect.left + WIDTH) / (int)BLOCK_SIZE); j++)
            {
                char el = (char)line[j];
                if (el == '#' || el == '+')
                {
                    if (is_reflected)
                    {
                        speed *= -1;
                    }
                    else
                    {
                        rect.left = start_x;
                        rect.top = start_y;
                    }
                }
            }
        }
    }

};

class Coin: public Entity
{
public:
    Coin(float init_x, float init_y);

    void update(float frame, LevelMap &level_map) override;

    void set_offset(sf::Vector2f player_offset);

private:
    float start_x;
    float start_y;

    static const unsigned int WIDTH = (unsigned int)(BLOCK_SIZE * 0.6);
    static const unsigned int HEIGHT = (unsigned int)(BLOCK_SIZE * 0.6);

    sf::Vector2f offset;

    float wobble = 0;
    float wobble_pos = 0;
    float wobble_dist = 5;
    float wobble_speed = 0.005;

    bool is_hits_wall = false;

    void check_block_collision(LevelMap &level_map)
    {
        float vert_pos = start_y + wobble_pos;
        for (int i = ((int)vert_pos / (int)BLOCK_SIZE); i <= ((int)(vert_pos + HEIGHT) / (int)BLOCK_SIZE); i++)
        {
            sf::String line = level_map.getLine(i);
            for (int j = ((int)rect.left / (int)BLOCK_SIZE); j <= ((int)(rect.left + WIDTH) / (int)BLOCK_SIZE); j++)
            {
                char el = (char)line[j];
                if (el == '#' || el == '+')
                {
                    is_hits_wall = true;
                }
            }
        }
    }

    static float random_wobble()
    {
        int scale = 10000;
        int scaled_limit = M_PI * 2 * scale;

        std::random_device rand_dev;
        std::default_random_engine generator{rand_dev()};
        std::uniform_int_distribution<int> distribution(0, scaled_limit);

        int rand_wobble = distribution(generator);
        float result = (float)rand_wobble / (float)scale;
        return result;
    }

};

#endif //MINIPLATFORM_ENTITIES_H
