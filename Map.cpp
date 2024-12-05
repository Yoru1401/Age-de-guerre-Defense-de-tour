#include "Map.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <stdexcept>

// Tile size in pixels
constexpr int TILE_SIZE = 64;

// Constructor
Map::Map(int rows, int cols, const std::string& tileTexturePath, const std::string& emptyTexturePath)
    : rows(rows), cols(cols) {
    if (!tileTexture.loadFromFile(tileTexturePath)) {
        throw std::runtime_error("Error: Unable to load tile texture!");
    }
    if (!mainGridTexture.loadFromFile(emptyTexturePath)) {
        throw std::runtime_error("Error: Unable to load grid texture!");
    }

    mainGrid = generateRandomGrid(rows, cols);

    // Set up sprites
    tileSprite.setTexture(tileTexture);
    tileSprite.setScale(TILE_SIZE / 16.f, TILE_SIZE / 16.f);

    redTile.setTexture(mainGridTexture);
    redTile.setScale(TILE_SIZE / 16.f, TILE_SIZE / 16.f);
}

// Draw tiles on the map
void Map::drawTiles(sf::RenderWindow& window) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            int tileIndex = computeTileIndex(y, x);
            sf::IntRect subImageRect((tileIndex % 4) * 16, (tileIndex / 4) * 16, 16, 16);
            tileSprite.setTextureRect(subImageRect);
            tileSprite.setPosition(static_cast<float>(x) * TILE_SIZE, static_cast<float>(y) * TILE_SIZE);
            window.draw(tileSprite);
        }
    }
}

// Generate a random grid with predefined tile patterns
std::vector<std::vector<Tile>> Map::generateRandomGrid(int rows, int cols) {
    std::vector<std::vector<Tile>> grid(rows, std::vector<Tile>(cols, Tiles[0]));

    grid[0][0] = Tiles[1];
    for (int x = 1; x < cols; ++x) grid[0][x] = Tiles[0];

    for (int y = 1; y < rows / 2; ++y) {
        grid[y][0] = Tiles[7];
        for (int x = 1; x < cols; ++x) grid[y][x] = Tiles[0];
    }

    grid[rows / 2][0] = Tiles[2];
    for (int x = 1; x < cols - 1; ++x) grid[rows / 2][x] = Tiles[6];
    grid[rows / 2][cols - 1] = Tiles[4];

    for (int y = rows / 2 + 1; y < rows - 1; ++y) {
        for (int x = 0; x < cols - 1; ++x) grid[y][x] = Tiles[0];
        grid[y][cols - 1] = Tiles[7];
    }

    for (int x = 0; x < cols - 1; ++x) grid[rows - 1][x] = Tiles[0];
    grid[rows - 1][cols - 1] = Tiles[11];

    return grid;
}

// Compute the tile index based on neighbors
int Map::computeTileIndex(int y, int x) const {
    auto isTileEmpty = [this](int row, int col) {
        return row < 0 || col < 0 || row >= rows || col >= cols || mainGrid[row][col] == Tiles[0];
    };

    return
        (isTileEmpty(y - 1, x - 1) * 8) +
        (isTileEmpty(y - 1, x) * 4) +
        (isTileEmpty(y, x - 1) * 2) +
        (isTileEmpty(y, x));
}

// Display the map on the window
void Map::display(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    drawTiles(window);
}

// Get the size of the map
sf::Vector2f Map::getMapSize() const {
    return {static_cast<float>(cols) * TILE_SIZE, static_cast<float>(rows) * TILE_SIZE};
}

const std::vector<std::vector<Tile>>& Map::getGrid() const {
    return mainGrid;
}

