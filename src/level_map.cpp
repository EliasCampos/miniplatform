//
// Created by elias on 11/24/21.
//

#include "../includes/miniplatform/level_map.h"


LevelMap::LevelMap() = default;


LevelMap::LevelMap(std::vector<sf::String> &level_map) {
    map_lines = level_map;
}

const sf::String& LevelMap::operator[](int index) {
    return map_lines[index];
}

int LevelMap::size() {
    return (int)map_lines.size();
}

