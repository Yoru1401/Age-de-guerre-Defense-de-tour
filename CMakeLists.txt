cmake_minimum_required(VERSION 3.29)
project(untitled)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:/SFML/")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)



add_executable(untitled fenetre_principale.cpp)



target_link_libraries(untitled sfml-graphics sfml-window sfml-system)

