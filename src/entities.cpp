//
// Created by elias on 22.02.2020.
//
#include <cmath>

#include <SFML/Graphics.hpp>

#include "../includes/miniplatform/settings.h"
#include "../includes/miniplatform/entities.h"


void Entity::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}
sf::FloatRect Entity::get_rect()
{
    sf::FloatRect rect_copy(rect);
    return rect_copy;
}

void Entity::update_display(LevelMap &level_map) {
    sf::Color current_color = level_map.create_time_stop_color(base_color);
    sprite.setFillColor(current_color);
}


Player::Player(sf::Vector2f init_pos)
{
    rect.left = init_pos.x;
    rect.top = init_pos.y;
    rect.width = WIDTH;
    rect.height = HEIGHT;
    base_color = sf::Color(50, 200, 100);
    sprite.setSize(sf::Vector2f(WIDTH, HEIGHT));
    sprite.setFillColor(base_color);
    dx = dy = 0;
    is_on_ground = false;
}
void Player::update(float time, LevelMap &level)
{
    if (!is_on_ground)
    {
        dy += gravity * time;
    }
    rect.top += dy * time;
    is_on_ground = false;
    check_block_collision(level, 1);
    rect.left += dx * time;
    check_block_collision(level, 0);
    auto offset = get_offset();
    sprite.setPosition(rect.left - offset.x, rect.top - offset.y);
    if (is_dead || is_won)
    {
        finalization_time -= time;
    }
    dx = 0;
}
// Motion control:
void Player::move_left(float time)
{
    dx = -player_step * time;
}
void Player::move_right(float time)
{
    dx = player_step * time;
}
void Player::jump()
{
    if (is_on_ground)
    {
        dy = -(float)3 * player_step;
        Effect::get_instance().perform(EffectType::JUMP);
    }
}
// State control:
void Player::set_position(sf::Vector2f position)
{
    rect.left = position.x;
    rect.top = position.y;
}
void Player::set_dead()
{
    if (!is_won && !is_dead) {
        is_dead = true;
        sprite.setFillColor(sf::Color::Red);
        Effect::get_instance().perform(EffectType::LAVA_TOUCH);
    }
}
void Player::set_won()
{
    if (!is_dead && !is_won) {
        is_won = true;
        sprite.setFillColor(sf::Color::Yellow);
        Effect::get_instance().perform(EffectType::LEVEL_END);
    }
}
// State info:
sf::Vector2f Player::get_offset()
{
    sf::Vector2f result(rect.left - (WINDOW_WIDTH / (float)2), rect.top - (WINDOW_HEIGHT / (float)2));
    return result;
}
bool Player::is_touches(Entity &entity)
{
    return entity.get_rect().intersects(rect);
}
void Player::touch_coin() {
    Effect::get_instance().perform(EffectType::COIN_TOUCH);
}

bool Player::is_died() const
{
    return !is_won && is_dead && finalization_time <= 0;
}
bool Player::is_winner() const
{
    return !is_dead && is_won && finalization_time <= 0;
}

void Player::update_display(LevelMap &level_map)
{}


Lava::Lava(float init_x, float init_y, bool is_repeat, bool is_horizontal, int direction)
{
    start_x = init_x;
    start_y = init_y;
    is_reflected = !is_repeat;
    is_vertical = !is_horizontal;
    rect.left = start_x;
    rect.top = start_y + lim * (float)direction;
    rect.width = WIDTH;
    rect.height = HEIGHT;
    base_color = sf::Color(255, 100, 100);
    sprite.setSize(sf::Vector2f(WIDTH, HEIGHT));
    sprite.setFillColor(base_color);
}
void Lava::set_offset(sf::Vector2f player_offset)
{
    offset.x = player_offset.x;
    offset.y = player_offset.y;
}
void Lava::update(float time, LevelMap &level)
{
    float current_speed = speed * level.time_acceleration_factor() * level.time_stop_factor();
    if (is_vertical)
    {
        rect.top += current_speed;
    }
    else
    {
        rect.left += current_speed;
    }
    check_block_collision(level);
    sprite.setPosition(rect.left - offset.x, rect.top - offset.y);
}


Coin::Coin(float init_x, float init_y)
{
    start_x = init_x;
    start_y = init_y;

    wobble = random_wobble();

    rect.left = start_x;
    rect.top = start_y;
    rect.width = WIDTH;
    rect.height = HEIGHT;
    base_color = sf::Color::Yellow;

    sprite.setSize(sf::Vector2f(WIDTH, HEIGHT));
    sprite.setFillColor(base_color);
}
void Coin::update(float frame, LevelMap &level_map)
{
    float current_wobble_speed = wobble_speed * level_map.time_acceleration_factor() * level_map.time_stop_factor();
    wobble += current_wobble_speed * frame;
    wobble_pos = (float)sin((double)wobble) * wobble_dist;
    check_block_collision(level_map);
    if (!is_hits_wall)
    {
        rect.top = start_y + wobble_pos;
    }
    is_hits_wall = false;
    sprite.setPosition(rect.left - offset.x, rect.top - offset.y);
}
void Coin::set_offset(sf::Vector2f player_offset)
{
    offset.x = player_offset.x;
    offset.y = player_offset.y;
}
