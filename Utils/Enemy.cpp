#include "Enemy.h"

#include <iostream>
#include <stdexcept>

constexpr int TILE_SIZE = 64;

// Constructeur
Enemy::Enemy(float speed, int health, const sf::Vector2f& startPosition)
    : speed(speed), health(health), maxHealth(health), position({startPosition.x + TILE_SIZE, startPosition.y + TILE_SIZE}), direction(0.f, 0.f) {
    shape.setRadius(10.f); // Rayon du cercle pour représenter l'ennemi
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(10.f, 10.f); // Centrer le cercle
    shape.setPosition(position);

    // Initialiser l'index de la tuile actuelle
    currentTileIndex = sf::Vector2i(static_cast<int>((startPosition.x)/ TILE_SIZE),
                                    static_cast<int>((startPosition.y)/ TILE_SIZE));




}

// Met à jour la position de l'ennemi
void Enemy::update(float deltaTime, const std::vector<std::vector<Tile>>& grid) {
    if (health <= 0) return; // Si l'ennemi est mort, il ne bouge plus


    // Récupérer la tuile actuelle
    if (currentTileIndex.y < 0 || currentTileIndex.x < 0 ||
        currentTileIndex.y >= static_cast<int>(grid.size()) ||
        currentTileIndex.x >= static_cast<int>(grid[0].size())) {
        throw std::out_of_range("Enemy is out of bounds!");
        }

    std::vector<Tile>::value_type currentTile = grid[currentTileIndex.y][currentTileIndex.x];

    // Calculer la direction basée sur la tuile
    movementVector = currentTile.processVectors(movementVector);


    direction = sf::Vector2f(static_cast<float>(movementVector[0]), static_cast<float>(movementVector[1]));

    // Mettre à jour la position
    position += direction * speed * deltaTime;

    // Mettre à jour la position graphique
    shape.setPosition(position);

    // Mettre à jour l'index de la tuile
    currentTileIndex = sf::Vector2i(static_cast<int>(position.x / TILE_SIZE)-1,
                                    static_cast<int>(position.y / TILE_SIZE)-1);
}
// Ajoutez ceci dans Enemy.cpp

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

sf::Vector2f Enemy::getPosition() const {
    return position;
}

void Enemy::draw(sf::RenderWindow& window) const {
    if (health > 0) {
        window.draw(shape);

        // Dessiner la barre de vie si l'ennemi n'a pas sa vie maximale
        if (health < maxHealth) {
            sf::RectangleShape healthBar(sf::Vector2f(20.f, 3.f));
            healthBar.setFillColor(sf::Color::Green);
            healthBar.setPosition(position.x - 10.f, position.y - 20.f);

            // Ajuster la largeur de la barre en fonction des PV restants
            healthBar.setScale(static_cast<float>(health) / maxHealth, 1.f);
            window.draw(healthBar);
        }
    }
}

Tile Enemy::getTile(const std::vector<std::vector<Tile> > &grid) const {
    return grid[currentTileIndex.y][currentTileIndex.x];
}

// Vérifie si l'ennemi est mort
bool Enemy::isDead() const {
    return health <= 0;
}
