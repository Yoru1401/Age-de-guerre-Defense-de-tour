cmake_minimum_required(VERSION 3.29)
project(TD)

set(CMAKE_CXX_STANDARD 20)

# Ajout du fichier source
add_executable(TD main.cpp
        Utils/Map.cpp
        Utils/Map.h
        Game.cpp
        Game.h
        Utils/Utils.h
        Utils/Enemy.cpp
        Utils/Enemy.h
        Utils/Tower.cpp
        Utils/Tower.h
        Utils/WaveManager.cpp
        Utils/WaveManager.h
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Assets)

# Localisation et liaison de SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
target_link_libraries(TD sfml-graphics sfml-window sfml-system sfml-audio)
