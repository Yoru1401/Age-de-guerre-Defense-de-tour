cmake_minimum_required(VERSION 3.29)
project(TD)

set(CMAKE_CXX_STANDARD 20)

# Ajout du fichier source
add_executable(TD
        Utils/Map.h
        Utils/Enemy.h
        Utils/Tower.h
        Utils/WaveManager.h

        main.cpp
        Menus/GameMenu.h
        Utils/Utils.h
        Menus/MainMenu.h
)

file(COPY cmake-build-debug/Assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Assets)

# Localisation et liaison de SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
target_link_libraries(TD sfml-graphics sfml-window sfml-system sfml-audio)
