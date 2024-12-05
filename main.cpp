#include <SFML/Graphics.hpp>
#include "Utils/Map.h"
#include <cmath>
#include <iostream>
#include <oneapi/tbb/task_arena.h>

#include "Utils/Enemy.h"
#include "Utils/Tower.h"
#include "Utils/WaveManager.h"

// Dimensions de la carte
constexpr int MAP_ROWS = 20;
constexpr int MAP_COLS = 20 * 1.3f;

// Taille des tuiles
constexpr int TILE_SIZE = 64;

int main() {
    // Dimensions de la fenêtre
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Carte Interactive");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    // Charger la carte
    Map map(MAP_ROWS + 1, MAP_COLS + 1, "Assets/Tile.png", "Assets/emptyTexture.png");
    WaveManager waveManager(2.f, 5, sf::Vector2f(0.f, 0.f)); // Spawn toutes les 2s, 5 ennemis par vague



    // Vue pour le déplacement et le zoom
    sf::View view;

    // Calcul de la taille totale de la carte
    float mapWidth = MAP_COLS * TILE_SIZE;
    float mapHeight = MAP_ROWS * TILE_SIZE;

    // Initialiser la vue pour afficher toute la carte
    view.setSize(mapWidth, mapHeight);
    view.setCenter(mapWidth / 2.0f, mapHeight / 2.0f);

    // Variables pour le déplacement
    sf::Vector2f dragStart;
    bool isDragging = false;


    // Créer un bouton
    sf::RectangleShape button(sf::Vector2f(100.f, 50.f));
    button.setFillColor(sf::Color(116, 66, 31));
    button.setOutlineColor(sf::Color(208, 134, 71));
    button.setOutlineThickness(2.f);
    button.setPosition(WINDOW_WIDTH - 110.f, WINDOW_HEIGHT - 60.f); // Coin inférieur droit

    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf")) {
        throw std::runtime_error("Erreur : Impossible de charger la police arial.ttf");
    }

    sf::Text buttonText("New Wave", font, 17);
    buttonText.setFillColor(sf::Color(208, 134, 71));
    buttonText.setPosition(button.getPosition().x + 10.f, button.getPosition().y + 10.f);
    buttonText.setOutlineThickness(1.f);
    buttonText.setOutlineColor(sf::Color(93, 43, 36));


    std::vector<Tower> towers;

    // Ajouter une tour sur une case disponible
    sf::Vector2i tileIndex(3, 9); // Exemple : case (5, 5)
    sf::Vector2f towerPosition(tileIndex.x * TILE_SIZE + TILE_SIZE / 2.f, tileIndex.y * TILE_SIZE + TILE_SIZE / 2.f);
    towers.emplace_back(towerPosition, 300.f, 1.f); // Portée 150, cadence 1 tir/sec


    tileIndex = {5, 9}; // Exemple : case (5, 5)
    towerPosition= {tileIndex.x * TILE_SIZE + TILE_SIZE / 2.f, tileIndex.y * TILE_SIZE + TILE_SIZE / 2.f};
    towers.emplace_back(towerPosition, 300.f, 1.f); // Portée 150, cadence 1 tir/sec


    tileIndex = {7, 9}; // Exemple : case (5, 5)
    towerPosition= {tileIndex.x * TILE_SIZE + TILE_SIZE / 2.f, tileIndex.y * TILE_SIZE + TILE_SIZE / 2.f};
    towers.emplace_back(towerPosition, 300.f, 1.f); // Portée 150, cadence 1 tir/sec



    int zoom = 0;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Mettre à jour la gestion des vagues
        waveManager.update(deltaTime, map.getGrid());

        // Mettre à jour les tours
        for (auto& tower : towers) {
            tower.update(deltaTime, waveManager.getEnemies());
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gestion du zoom avec la molette
            if (event.type == sf::Event::MouseWheelScrolled) {
                float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;

                if (!(zoom == 0 && zoomFactor > 1)) {
                    view.zoom(zoomFactor);
                    zoom += zoomFactor < 1 ? 1 : -1;
                }


                std::cout << "zoom = " << zoom << std::endl;
            }

            // Gestion du clic droit pour déplacer la carte
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                isDragging = true;
                dragStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
                isDragging = false;
            }

            // Gestion du clic gauche pour le bouton
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    if (!waveManager.isWaveInProgress()) {
                        waveManager.startWave();
                    }
                }
            }
        }



        // Gestion du déplacement pendant le clic droit
        if (isDragging) {
            sf::Vector2f currentPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f offset = dragStart - currentPos;
            view.move(offset);

            // Limiter le déplacement aux bords de la carte
            sf::Vector2f viewCenter = view.getCenter();
            sf::Vector2f viewSize = view.getSize();

            float halfWidth = viewSize.x / 2.0f;
            float halfHeight = viewSize.y / 2.0f;

            float leftBound = halfWidth;
            float rightBound = (MAP_COLS * TILE_SIZE) - halfWidth;
            float topBound = halfHeight;
            float bottomBound = (MAP_ROWS * TILE_SIZE) - halfHeight;

            // Corriger les positions pour rester dans les limites
            if (rightBound < leftBound) rightBound = leftBound;  // Cas rare de vue plus grande que la carte
            if (bottomBound < topBound) bottomBound = topBound;

            viewCenter.x = std::clamp(viewCenter.x, leftBound, rightBound);
            viewCenter.y = std::clamp(viewCenter.y, topBound, bottomBound);

            view.setCenter(viewCenter);

        }

        // Rendu de la carte
        window.clear(sf::Color::Black);
        window.setView(view);
        map.display(window);

        // Dessiner les tours
        for (auto& tower : towers) {
            tower.draw(window);
        }


        // Dessiner les ennemis
        for (const auto& enemy : waveManager.getEnemies()) {
            enemy.draw(window);
        }


        window.setView(window.getDefaultView()); // Utiliser la vue par défaut pour que le bouton reste fixe
        window.draw(button);
        window.draw(buttonText);

        window.display();
    }

    return 0;
}

