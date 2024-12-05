#include "Tower.h"

#include <cmath>

// Constructeur
Tower::Tower(const sf::Vector2f& position, float range, float fireRate)
    : position(position), range(range), fireRate(fireRate), timeSinceLastShot(0.f) {}

// Met à jour la tour (tir des projectiles)
void Tower::update(float deltaTime, std::vector<Enemy>& enemies) {
    timeSinceLastShot += deltaTime;

    // Vérifier si un ennemi est dans la portée
    for (auto& enemy : enemies) {
        if (!enemy.isDead()) {
            sf::Vector2f enemyPos = enemy.getPosition();
            float distance = std::hypot(enemyPos.x - position.x, enemyPos.y - position.y);

            // Tirer sur l'ennemi si dans la portée et si prêt à tirer
            if (distance <= range && timeSinceLastShot >= 1.f / fireRate) {
                sf::CircleShape bullet(5.f);
                bullet.setFillColor(sf::Color::Yellow);
                bullet.setPosition(position);
                bullets.push_back(bullet);

                timeSinceLastShot = 0.f;
                break; // Tirer uniquement sur un ennemi à la fois
            }
        }
    }

    // Mettre à jour la position des projectiles et vérifier les collisions
    for (auto it = bullets.begin(); it != bullets.end();) {
        sf::Vector2f bulletPos = it->getPosition();
        sf::Vector2f direction;

        // Trouver le premier ennemi vivant
        for (auto& enemy : enemies) {
            if (!enemy.isDead()) {
                sf::Vector2f enemyPos = enemy.getPosition();
                direction = enemyPos - bulletPos;
                float magnitude = std::hypot(direction.x, direction.y);
                if (magnitude > 0) direction /= magnitude;

                // Déplacer le projectile
                it->move(direction * 3000.f * deltaTime); // Vitesse du projectile

                // Vérifier si le projectile touche l'ennemi
                if (magnitude < 10.f) {
                    enemy.takeDamage(10); // Inflige 10 points de dégâts
                    it = bullets.erase(it); // Supprimer le projectile
                    break;
                }
            }
        }

        if (it != bullets.end()) ++it;
    }
}

// Dessine la tour et les projectiles
void Tower::draw(sf::RenderWindow& window) {
    // Dessiner la tour
    sf::CircleShape tower(15.f);
    tower.setFillColor(sf::Color::Blue);
    tower.setOrigin(15.f, 15.f);
    tower.setPosition(position);
    window.draw(tower);

    // Dessiner les projectiles
    for (const auto& bullet : bullets) {
        window.draw(bullet);
    }
}
