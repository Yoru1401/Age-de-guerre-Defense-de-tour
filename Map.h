#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <string>

class Map {
public:
    // Constructeur
    Map(int rows, int cols, const std::string& tileTexturePath);

    // Méthodes pour dessiner les grilles
    void display(sf::RenderWindow& window);


private:
    // Dimensions de la grille
    int rows, cols;

    // Grille principale
    std::vector<std::vector<int>> mainGrid;

    // Ressources graphiques
    sf::Texture tileTexture;
    sf::Sprite tileSprite;
    sf::RectangleShape redTile;

    // Méthodes utilitaires
    static std::vector<std::vector<int>> generateRandomGrid(int rows, int cols);
    int computeTileIndex(int y, int x) const;

    void drawTiles(sf::RenderWindow& window);
    void drawGrid(sf::RenderWindow& window);
};

#endif // MAP_H
