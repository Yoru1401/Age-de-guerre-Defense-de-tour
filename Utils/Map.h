#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
constexpr int TILE_SIZE = 64;

struct Tile {
    char symbol;
    std::vector<std::string> dir;

    std::vector<int> processVectors(const std::vector<int>& intVec) {

        if (intVec.size() != 2 || dir.size() != 2) {
            throw std::invalid_argument("Both input vectors must have exactly 2 elements.");
        }

        std::vector<int> result(2);

        for (size_t i = 0; i < 2; ++i) {
            if (dir[i] == "0" || dir[i] == "1" || dir[i] == "-1") {
                // Convert directly from string to int
                result[i] = std::stoi(dir[i]);
            } else if (dir[i] == "X") {
                result[i] = intVec[0];
            } else if (dir[i] == "-X") {
                result[i] = -intVec[0];
            } else if (dir[i] == "Y") {
                result[i] = intVec[1];
            } else if (dir[i] == "-Y") {
                result[i] = -intVec[1];
            } else {
                throw std::invalid_argument("Invalid string value in strVec: " + dir[i]);
            }
        }

        return result;
    }

    bool operator==(const Tile & tile) const = default;
};

// Tile definitions
const std::vector Tiles = {
    Tile('T', {"0", "0"}), Tile('O', {"0", "1"}),
    Tile('>', {"1", "0"}), Tile('<', {"-1", "0"}),
    Tile('v', {"0", "1"}), Tile('^', {"0", "-1"}),
    Tile('-', {"X", "0"}), Tile('|', {"0", "Y"}),
    Tile('+', {"X", "Y"}), Tile('/', {"-Y", "-X"}),
    Tile('\\', {"Y", "X"}), Tile('X', {"0", "0"})
};


class Map {
public:
    // Constructeur
    Map(int rows, int cols, const std::string& tileTexturePath, const std::string& emptyTexturePath)
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

    sf::Vector2f getMapSize() const {
        return {static_cast<float>(cols) * TILE_SIZE, static_cast<float>(rows) * TILE_SIZE};
    }

    const std::vector<std::vector<Tile>> &getGrid() const {
        return mainGrid;
    }

    void display(sf::RenderWindow& window) {
        window.clear(sf::Color::Black);
        drawTiles(window);
    }

private:
    // Dimensions de la grille
    int rows, cols;

    // Grille principale
    std::vector<std::vector<Tile>> mainGrid;

    // Ressources graphiques
    sf::Texture tileTexture;
    sf::Sprite tileSprite;

    sf::Texture mainGridTexture;
    sf::Sprite redTile;


    // Méthodes utilitaires
    static std::vector<std::vector<Tile>> generateRandomGrid(int rows, int cols) {
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

    int computeTileIndex(int y, int x) const {
        auto isTileEmpty = [this](int row, int col) {
            return row < 0 || col < 0 || row >= rows || col >= cols || mainGrid[row][col] == Tiles[0];
        };

        return
            (isTileEmpty(y - 1, x - 1) * 8) +
            (isTileEmpty(y - 1, x) * 4) +
            (isTileEmpty(y, x - 1) * 2) +
            (isTileEmpty(y, x));
    }


    void drawTiles(sf::RenderWindow& window) {
        for (int y = 0; y < rows +1; ++y) {
            for (int x = 0; x < cols +1; ++x) {
                int tileIndex = computeTileIndex(y, x);
                sf::IntRect subImageRect((tileIndex % 4) * 16, (tileIndex / 4) * 16, 16, 16);
                tileSprite.setTextureRect(subImageRect);
                tileSprite.setPosition(static_cast<float>(x) * TILE_SIZE, static_cast<float>(y) * TILE_SIZE);
                window.draw(tileSprite);
            }
        }
    }

};

#endif // MAP_H
