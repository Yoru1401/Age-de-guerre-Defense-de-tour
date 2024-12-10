#include <SFML/Graphics.hpp>
#include "../Utils/Map.h"
#include <cmath>
#include <iostream>
#include <oneapi/tbb/task_arena.h>
#include "../Utils/Enemy.h"
#include "../Utils/Tower.h"
#include "../Utils/WaveManager.h"

class GameMenu {
public:
    GameMenu(sf::RenderWindow& window)
        : window(window),
          map(MAP_ROWS, MAP_COLS, "Assets/Tile.png", "Assets/emptyTexture.png"),
          waveManager(2.f, 5, sf::Vector2f(0.f, 0.f)) {

        if (!font.loadFromFile("Assets/arial.ttf")) {
            throw std::runtime_error("Erreur : Impossible de charger la police arial.ttf");
        }

        if (!barrackTexture.loadFromFile("Assets/barrack.png")) {
            throw std::runtime_error("Erreur : Impossible de charger barrack.png");
        }

        const auto& grid = map.getGrid();
        for (int y = 0; y < MAP_ROWS; ++y) {
            for (int x = 0; x < MAP_COLS; ++x) {
                if (grid[y][x] == Tiles[0]) { // Vérifie si la case est de type Tile[0]
                    sf::RectangleShape overlay(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    overlay.setFillColor(sf::Color(168,200,92, 100)); // Vert transparent
                    overlay.setPosition(x * TILE_SIZE + 32, y * TILE_SIZE +32);
                    gridOverlays.push_back(overlay);
                }
            }
        }


        setupView();
        setupButton();
    }

    void run() {
        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();

            waveManager.update(deltaTime, map.getGrid());
            for (auto& tower : towers) {
                tower.update(deltaTime, waveManager.getEnemies());
            }

            if (handleEvents()) {return;};
            render();
        }
    }

private:
    static constexpr int MAP_ROWS = 20;
    static constexpr int MAP_COLS = 20 * 1.3f;
    static constexpr int TILE_SIZE = 64;

    sf::RenderWindow& window;
    sf::Clock clock;
    sf::Font font;
    sf::View view;
    sf::CircleShape button;
    sf::Text buttonText;
    Map map;
    WaveManager waveManager;
    std::vector<Tower> towers;
    sf::Vector2f dragStart;
    bool isDragging = false;
    int zoom = 0;

    std::vector<sf::RectangleShape> gridOverlays;
    sf::Texture barrackTexture;
    std::vector<sf::Sprite> placedBarracks;

    void setupView() {
        float mapWidth = (MAP_COLS + 1) * TILE_SIZE;
        float mapHeight = (MAP_ROWS + 1) * TILE_SIZE;

        view.setSize(mapWidth, mapHeight);
        view.setCenter(mapWidth / 2.0f, mapHeight / 2.0f);
    }

    void setupButton() {
        button.setRadius(50.f);
        button.setFillColor(sf::Color(116, 66, 31));
        button.setOutlineColor(sf::Color(208, 134, 71));
        button.setOutlineThickness(2.f);
        button.setPosition(window.getSize().x - 110.f, window.getSize().y - 110.f);

        buttonText.setFont(font);
        buttonText.setString("New Wave");
        buttonText.setCharacterSize(17);
        buttonText.setFillColor(sf::Color(208, 134, 71));
        buttonText.setPosition(button.getPosition().x + 10.f, button.getPosition().y + 35.f);
        buttonText.setOutlineThickness(1.f);
        buttonText.setOutlineColor(sf::Color(93, 43, 36));
    }

    void addTower(int row, int col) {
        sf::Vector2f position(col * TILE_SIZE + TILE_SIZE / 2.f, row * TILE_SIZE + TILE_SIZE / 2.f);
        towers.emplace_back(position, 300.f, 1.f);
    }

    bool handleEvents() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                return true;;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                for (const auto& overlay : gridOverlays) {
                    if (overlay.getGlobalBounds().contains(worldPos)) {
                        sf::Sprite barrackSprite;
                        barrackSprite.setTexture(barrackTexture);
                        barrackSprite.setPosition(overlay.getPosition());

                        addTower(worldPos.y/TILE_SIZE, worldPos.x/TILE_SIZE);
                        placedBarracks.push_back(barrackSprite);
                        break;
                    }
                }
            }

            handleZoom(event);
            handleDragging(event);
            handleButtonClick(event);
        }

        if (isDragging) {
            updateViewDragging();
        }
        return false;
    }

    void handleZoom(const sf::Event& event) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            float zoomFactor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
            if (!(zoom == 0 && zoomFactor > 1) && !(zoom == 5 && zoomFactor < 1)) {
                view.zoom(zoomFactor);
                zoom += zoomFactor < 1 ? 1 : -1;
            }
        }
    }

    void handleDragging(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            isDragging = true;
            dragStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
            isDragging = false;
        }
    }

    void handleButtonClick(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                if (!waveManager.isWaveInProgress()) {
                    waveManager.startWave();
                }
            }
        }
    }

    void updateViewDragging() {
        sf::Vector2f currentPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f offset = dragStart - currentPos;
        view.move(offset);

        float mapWidth = (MAP_COLS + 1) * TILE_SIZE;
        float mapHeight = (MAP_ROWS + 1) * TILE_SIZE;
        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();

        float halfWidth = viewSize.x / 2.0f;
        float halfHeight = viewSize.y / 2.0f;
        viewCenter.x = std::clamp(viewCenter.x, halfWidth, mapWidth - halfWidth);
        viewCenter.y = std::clamp(viewCenter.y, halfHeight, mapHeight - halfHeight);

        view.setCenter(viewCenter);
    }

    void render() {
        window.clear(sf::Color::Black);
        window.setView(view);
        map.display(window);

        for (const auto& overlay : gridOverlays) {
            window.draw(overlay);
        }

        for (const auto& barrack : placedBarracks) {
            window.draw(barrack);
        }

        for (auto& tower : towers) {
            tower.draw(window);
        }

        for (const auto& enemy : waveManager.getEnemies()) {
            enemy.draw(window);
        }

        window.setView(window.getDefaultView());
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
};


