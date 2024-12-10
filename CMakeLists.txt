
cmake_minimum_required(VERSION 3.29)
project(TD)

set(CMAKE_CXX_STANDARD 20)

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
include_directories(headers /usr/include d:/SFML/SFML-2.6.2/include)

set(SFML_ROOT d:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TD ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/Assets)

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()