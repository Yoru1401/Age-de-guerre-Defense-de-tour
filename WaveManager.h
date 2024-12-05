#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class WaveManager {
public:
    WaveManager(float spawnInterval, int enemiesPerWave, const sf::Vector2f& spawnPoint);

    // Met à jour la vague (génération des ennemis)
    void update(float deltaTime, const std::vector<std::vector<Tile>> &map);

    // Lancer une nouvelle vague
    void startWave();

    // Vérifier si une vague est en cours
    bool isWaveInProgress() const;

    // Récupérer la liste des ennemis
    std::vector<Enemy>& getEnemies();

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
