#include "WaveManager.h"

// Constructeur
WaveManager::WaveManager(float spawnInterval, int enemiesPerWave, const sf::Vector2f& spawnPoint)
    : spawnInterval(spawnInterval), enemiesPerWave(enemiesPerWave), spawnPoint(spawnPoint),
      timeSinceLastSpawn(0.f), enemiesSpawned(0), waveInProgress(false) {}

// Lancer une nouvelle vague
void WaveManager::startWave() {
    waveInProgress = true;
    timeSinceLastSpawn = 0.f;
    enemiesSpawned = 0;
    enemies.clear(); // Nettoyer les ennemis restants (s'il y en a)
}

// Vérifier si une vague est en cours
bool WaveManager::isWaveInProgress() const {
    return waveInProgress;
}

// Met à jour la vague
void WaveManager::update(const float deltaTime, const std::vector<std::vector<Tile>>& map) {
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

// Récupérer la liste des ennemis
std::vector<Enemy>& WaveManager::getEnemies() {
    return enemies;
}
