cmake_minimum_required(VERSION 3.15)
project(miniplatform)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

add_executable(miniplatform main.cpp includes/miniplatform/entities.h includes/miniplatform/level.h src/level.cpp src/entities.cpp includes/miniplatform/settings.h includes/miniplatform/game.h src/game.cpp includes/miniplatform/effect.h src/effect.cpp includes/miniplatform/level_map.h src/level_map.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(miniplatform ${SFML_LIBRARIES})
endif()
