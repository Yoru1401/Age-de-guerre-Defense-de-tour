cmake_minimum_required(VERSION 3.29)
project(TD)

set(CMAKE_CXX_STANDARD 20)

# Ajout du fichier source
add_executable(TD main.cpp
        Map.cpp
        Map.h
        Map.cpp
)

configure_file(TilemapDemo_1.png TilemapDemo_1.png COPYONLY)

# Localisation et liaison de SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(TD sfml-graphics sfml-window sfml-system)
