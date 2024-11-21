cmake_minimum_required(VERSION 3.29)
project(TowerDefense)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:/Users/yohan/Downloads/SFML/")

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(TowerDefense main.cpp
        Button.h
        Menu.h)


target_link_libraries(TowerDefense sfml-system sfml-window sfml-graphics sfml-audio)