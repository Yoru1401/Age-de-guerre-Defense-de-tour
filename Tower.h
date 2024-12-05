#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

class Tower {
public:
    // Constructeur
    Tower(const sf::Vector2f& position, float range, float fireRate);

    // Met à jour la tour (détection et tir)
    void update(float deltaTime, std::vector<Enemy>& enemies);

    // Dessine la tour et ses projectiles
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;               // Position de la tour
    float range;                         // Portée de la tour
    float fireRate;                      // Cadence de tir (projectiles par seconde)
    float timeSinceLastShot;             // Temps écoulé depuis le dernier tir
    std::vector<sf::CircleShape> bullets; // Liste des projectiles
};

#endif // TOWER_H
