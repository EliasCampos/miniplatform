//
// Created by elias on 11/24/21.
//

#ifndef MINIPLATFORM_LEVEL_MAP_H
#define MINIPLATFORM_LEVEL_MAP_H

#include <vector>
#include <SFML/Graphics.hpp>


class LevelMap
{
public:
    LevelMap();

    explicit LevelMap(std::vector<sf::String> &level_map);

    const sf::String &getLine(int index);

    int getHeight();

    void update(float frame);

    void set_time_stop();

    float time_stop_factor() const;  // in interval 1 to 0. 1 means no time stop, 0 means time stopped completely

    void accelerate_time(float acceleration);

    float time_acceleration_factor() const;

    sf::Color create_time_stop_color(sf::Color& color) const;

private:
    static const int FREEZE_TIME = 5;
    static const int DEFAULT_TIME_STOP_LEFT = FREEZE_TIME + 1;

    std::vector<sf::String> map_lines;
    bool is_time_stopped = false;
    float time_stop_left = (float)DEFAULT_TIME_STOP_LEFT;
    float time_stop_idle = 0;

    float time_acceleration = 1;
};


#endif //MINIPLATFORM_LEVEL_MAP_H
