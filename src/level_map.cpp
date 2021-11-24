//
// Created by elias on 11/24/21.
//

#include "../includes/miniplatform/effect.h"
#include "../includes/miniplatform/level_map.h"


LevelMap::LevelMap() = default;


LevelMap::LevelMap(std::vector<sf::String> &level_map) {
    map_lines = level_map;
}

const sf::String &LevelMap::getLine(int index) {
    return map_lines[index];
}

int LevelMap::getHeight() {
    return (int)map_lines.size();
}

void LevelMap::update(float frame) {
    float second_passed = frame * 800 / 1000000;
    if (is_time_stopped)
    {
        time_stop_left -= second_passed;
        if (time_stop_left <= 0) {
            is_time_stopped = false;
            time_stop_left = (float)DEFAULT_TIME_STOP_LEFT;
        }
    }
    else if (time_stop_idle > 0) {
        time_stop_idle -= second_passed;
    }
}

void LevelMap::set_time_stop() {
    if (!is_time_stopped and time_stop_idle <= 0) {
        is_time_stopped = true;
        time_stop_idle = DEFAULT_TIME_STOP_LEFT;

        Effect::get_instance().perform(EffectType::TIME_STOP);
    }
}

float LevelMap::time_stop_factor() const {
    if (!is_time_stopped) {
        return 1;
    }

    auto freeze_time = (float)FREEZE_TIME;
    if (time_stop_left - freeze_time > 0) {
        return ((time_stop_left - freeze_time) / (DEFAULT_TIME_STOP_LEFT - freeze_time));
    }

    return 0;
}

sf::Color LevelMap::create_time_stop_color(sf::Color &color) const
{
    float factor = time_stop_factor();
    if (time_stop_factor() < 1 && time_stop_factor() > 0)
    {
        float _r = ((float)(255 - color.r) * (1 - factor) + (float)color.r * factor) / 2;
        float _g = ((float)(255 - color.g) * (1 - factor) + (float)color.g * factor) / 2;
        float _b = ((float)(255 - color.b) * (1 - factor) + (float)color.b * factor) / 2;

        return {(sf::Uint8)(_r), (sf::Uint8)(_g), (sf::Uint8)(_b)};
    }
    return color;
}

void LevelMap::accelerate_time(float acceleration) {
    time_acceleration += acceleration;
}

float LevelMap::time_acceleration_factor() const {
    return time_acceleration;
}
