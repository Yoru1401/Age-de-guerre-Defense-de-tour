#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class WaveManager {
public:
    WaveManager(float spawnInterval, int enemiesPerWave, const sf::Vector2f& spawnPoint)
    : spawnInterval(spawnInterval), enemiesPerWave(enemiesPerWave), spawnPoint(spawnPoint),
      timeSinceLastSpawn(0.f), enemiesSpawned(0), waveInProgress(false) {}

    // Met à jour la vague (génération des ennemis)
    void update(const float deltaTime, const std::vector<std::vector<Tile>>& map) {
        if (!waveInProgress) return;

        timeSinceLastSpawn += deltaTime;

        // Générer un nouvel ennemi si le délai est respecté
        if (timeSinceLastSpawn >= spawnInterval && enemiesSpawned < enemiesPerWave) {
            enemies.emplace_back(100.f, 100, spawnPoint); // Exemple : vitesse 100, vie 10
            timeSinceLastSpawn = 0.f;
            ++enemiesSpawned;
        }

        // Mettre à jour les ennemis
        for (auto it = enemies.begin(); it != enemies.end();) {
            it->update(deltaTime, map);
            if (it->isDead() || it->getTile(map).symbol == 'X') {
                it = enemies.erase(it); // Supprimer les ennemis morts
            } else {
                ++it;
            }
        }

        // Terminer la vague si tous les ennemis sont morts et tous sont apparus
        if (enemies.empty() && enemiesSpawned >= enemiesPerWave) {
            waveInProgress = false;
        }
    }

    // Lancer une nouvelle vague
    void startWave() {
        waveInProgress = true;
        timeSinceLastSpawn = 0.f;
        enemiesSpawned = 0;
        enemies.clear(); // Nettoyer les ennemis restants (s'il y en a)
    }

    // Vérifier si une vague est en cours
    bool isWaveInProgress() const {
        return waveInProgress;
    }

    // Récupérer la liste des ennemis
    std::vector<Enemy>& getEnemies() {
        return enemies;
    }

private:
    float spawnInterval;          // Intervalle entre les spawns
    int enemiesPerWave;           // Nombre total d'ennemis par vague
    sf::Vector2f spawnPoint;      // Point d'apparition des ennemis

    float timeSinceLastSpawn;     // Temps écoulé depuis le dernier spawn
    int enemiesSpawned;           // Nombre d'ennemis déjà apparus
    bool waveInProgress;          // Indique si une vague est en cours

    std::vector<Enemy> enemies;   // Liste des ennemis actifs
};

#endif // WAVEMANAGER_H
