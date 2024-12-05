#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>

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
    Map(int rows, int cols, const std::string& tileTexturePath, const std::string& tileSpritePath);


    sf::Vector2f getMapSize() const;

    const std::vector<std::vector<Tile>> &getGrid() const;

    void display(sf::RenderWindow &window);

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
    static std::vector<std::vector<Tile>> generateRandomGrid(int rows, int cols);
    int computeTileIndex(int y, int x) const;


    void drawTiles(sf::RenderWindow &window);

};

#endif // MAP_H
