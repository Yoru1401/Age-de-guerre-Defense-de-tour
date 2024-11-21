#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

constexpr int TILE_SIZE = 64;

int main() {
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(fullscreenMode, "Dual-Grid Tiling", sf::Style::Fullscreen);

    int rows = static_cast<int>(fullscreenMode.height) / TILE_SIZE - 1;
    int cols = static_cast<int>(fullscreenMode.width) / TILE_SIZE - 1;

    try {
        Map map(rows, cols, "TilemapDemo_1.png");

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    window.close();
                    }
            }

            window.clear(sf::Color::Black);
            map.display(window);

            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
