#include "Map.h"

// Taille des tuiles
constexpr int TILE_SIZE = 64;

Map::Map(int rows, int cols, const std::string& tileTexturePath)
    : rows(rows), cols(cols) {
    // Charger la texture pour les tuiles
    if (!tileTexture.loadFromFile(tileTexturePath)) {
        throw std::runtime_error("Erreur : Impossible de charger l'image des tuiles !");
    }

    // Initialiser les grilles
    mainGrid = generateRandomGrid(rows, cols);

    // Configurer le sprite pour les tuiles
    tileSprite.setTexture(tileTexture);
    tileSprite.setScale(TILE_SIZE / 16.f, TILE_SIZE / 16.f);

    // Configurer les contours des cases
    redTile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    redTile.setFillColor(sf::Color::Transparent);
    redTile.setOutlineColor(sf::Color::White);
    redTile.setOutlineThickness(1);
}

void Map::drawTiles(sf::RenderWindow& window) {
    for (int y = 0; y <= rows; ++y) {
        for (int x = 0; x <= cols; ++x) {
            int tile = computeTileIndex(y, x);
            sf::IntRect subImageRect((tile % 4) * 16, (tile / 4) * 16, 16, 16);
            tileSprite.setTextureRect(subImageRect);
            tileSprite.setPosition(static_cast<float>(x) * TILE_SIZE, static_cast<float>(y) * TILE_SIZE);
            window.draw(tileSprite);
        }
    }
}

void Map::drawGrid(sf::RenderWindow& window) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            redTile.setPosition((static_cast<float>(x) + 0.5f) * TILE_SIZE, (static_cast<float>(y) + 0.5f) * TILE_SIZE);
            window.draw(redTile);
        }
    }
}

std::vector<std::vector<int>> Map::generateRandomGrid(int rows, int cols) {
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = rand() % 2; // 0 ou 1
        }
    }
    return grid;
}

int Map::computeTileIndex(int y, int x) const {
    return
        (!(y - 1 < 0 || x - 1 < 0 || mainGrid[y - 1][x - 1] > 0) * 8) +
        (!(y - 1 < 0 || x == cols || mainGrid[y - 1][x] > 0) * 4) +
        (!(y == rows || x - 1 < 0 || mainGrid[y][x - 1] > 0) * 2) +
        (!(y == rows || x == cols || mainGrid[y][x] > 0));
}

void Map::display(sf::RenderWindow& window) {
    // Affiche les deux grilles
    drawTiles(window);
    drawGrid(window);
}
