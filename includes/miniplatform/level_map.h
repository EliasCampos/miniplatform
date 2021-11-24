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

    const sf::String& operator[](int index);

    int size();

private:
    std::vector<sf::String> map_lines;
};


#endif //MINIPLATFORM_LEVEL_MAP_H
