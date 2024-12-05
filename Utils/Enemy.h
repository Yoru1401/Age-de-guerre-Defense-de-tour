#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"

class Enemy {
public:
    // Constructeur
    Enemy(float speed, int health, const sf::Vector2f& startPosition);
    sf::Vector2i currentTileIndex; // Position actuelle dans la grille (row, col)

    // Met à jour la position de l'ennemi en fonction du chemin et de la vitesse
    void update(float deltaTime, const std::vector<std::vector<Tile>>& grid);

    void takeDamage(int damage);
    sf::Vector2f getPosition() const;


    // Dessine l'ennemi à l'écran
    void draw(sf::RenderWindow& window) const;

    Tile getTile(const std::vector<std::vector<Tile> > &grid) const;

    // Vérifie si l'ennemi est mort
    bool isDead() const;

private:
    float speed;                   // Vitesse de déplacement
    int health;                    // Points de vie
    int maxHealth;
    sf::Vector2f position;         // Position actuelle
    sf::Vector2f direction;        // Direction actuelle (basée sur la tuile)
    sf::CircleShape shape;         // Représentation graphique de l'ennemi
    std::vector<int> movementVector = {1, 1};
};

#endif // ENEMY_H
