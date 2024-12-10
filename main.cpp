#include <iostream>
#include <SFML/Audio.hpp>

#include "Menus/GameMenu.h"
#include "Menus/MainMenu.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 1920), "Main Menu", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    float volume = 50.0f;
    sf::Music music;
    if (!music.openFromFile("Assets/music.ogg")) {
        std::cerr << "Erreur: Impossible de charger la musique." << std::endl;
        return -1;
    }
    music.setVolume(volume);
    music.play();
    music.setLoop(true);

    MainMenu mainMenu(window, volume, music);

    while (window.isOpen())
    {
        if (mainMenu.run()) {
            GameMenu gameMenu(window);
            gameMenu.run();
        }
    }

    return 0;
}
