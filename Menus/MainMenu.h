#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/Map.h"
#include <iostream>

inline void adjustTextToButton(sf::Text &text, const sf::RectangleShape &button) {
    const float padding = 10.0f; // Marge entre le texte et les bords du bouton
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    while (true) {
        sf::FloatRect textBounds = text.getLocalBounds();
        if (textBounds.width + padding < buttonBounds.width &&
            textBounds.height + padding < buttonBounds.height) {
            break;
        }

        text.setCharacterSize(text.getCharacterSize() - 1);
        if (text.getCharacterSize() <= 5) {
            break;
        }
    }

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(
        buttonBounds.left + buttonBounds.width / 2.0f,
        buttonBounds.top + buttonBounds.height / 2.0f
    );
}

// Fonction pour afficher la fenêtre des paramètres
inline void showSettingsWindow(float &volume, sf::RenderWindow &mainWindow, sf::Music &music) {
    sf::RenderWindow settingsWindow(sf::VideoMode(400, 300), "Options", sf::Style::None);
    settingsWindow.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police." << std::endl;
        return;
    }

    const float barWidth = 200.0f;
    sf::RectangleShape volumeBar(sf::Vector2f(barWidth, 10));
    volumeBar.setFillColor(sf::Color::White);
    volumeBar.setPosition(100, 100);

    sf::CircleShape volumeKnob(10);
    volumeKnob.setFillColor(sf::Color::Blue);
    volumeKnob.setOrigin(10, 10);
    volumeKnob.setPosition(volumeBar.getPosition().x + (volume / 100.0f) * barWidth, volumeBar.getPosition().y + 5);

    sf::Text volumeText("Volume", font, 20);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition(100, 70);

    sf::RectangleShape backButton(sf::Vector2f(100, 40));
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(150, 200);

    sf::Text backText("Retour", font, 20);
    backText.setFillColor(sf::Color::White);
    adjustTextToButton(backText, backButton);

    bool isDragging = false;
    bool settingsOpen = true;

    while (settingsOpen) {
        sf::Event event;
        while (settingsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                settingsOpen = false;
            }

            sf::Vector2f mousePos = settingsWindow.mapPixelToCoords(sf::Mouse::getPosition(settingsWindow));

            if (event.type == sf::Event::MouseButtonPressed) {
                if (volumeBar.getGlobalBounds().contains(mousePos)) {
                    isDragging = true; // Active le mode glissement
                }
                if (backButton.getGlobalBounds().contains(mousePos)) {
                    settingsOpen = false;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                isDragging = false; // Désactive le mode glissement
            }

            if (event.type == sf::Event::MouseMoved) {
                if (isDragging) {
                    float newVolume = ((mousePos.x - volumeBar.getPosition().x) / barWidth) * 100.0f;
                    volume = std::clamp(newVolume, 0.0f, 100.0f);
                    volumeKnob.setPosition(volumeBar.getPosition().x + (volume / 100.0f) * barWidth, volumeBar.getPosition().y + 5);
                    std::cout << "Volume: " << volume << "%" << std::endl;
                    // Mettre à jour le volume de la musique
                    music.setVolume(volume);
                }
            }
        }

        settingsWindow.clear(sf::Color::Black);
        settingsWindow.draw(volumeBar);
        settingsWindow.draw(volumeKnob);
        settingsWindow.draw(volumeText);
        settingsWindow.draw(backButton);
        settingsWindow.draw(backText);
        settingsWindow.display();
    }
}


class MainMenu {
public:
    MainMenu(sf::RenderWindow& window, float& volume, sf::Music& music)
        : window(window), volume(volume), music(music) {

        if (!backgroundTexture.loadFromFile("Assets/fond.jpg")) {
            throw std::runtime_error("Erreur : Impossible de charger le fond.");
        }

        backgroundSprite.setTexture(backgroundTexture);
        sf::Vector2u textureSize = backgroundTexture.getSize();
        sf::Vector2u windowSize = window.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);

        if (!font.loadFromFile("Assets/arial.ttf")) {
            throw std::runtime_error("Erreur : Impossible de charger la police.");
        }

        setupMenu();
    }

    bool run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        return true;
                    }
                    if (parametreButton.getGlobalBounds().contains(mousePos)) {
                        showSettingsWindow(volume, window, music);
                    }
                    if (quitButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
            }

            render();
        }
        return false;
    }

private:
    sf::RenderWindow& window;
    float& volume;
    sf::Music& music;
    sf::Font font;


    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    sf::RectangleShape playButton;
    sf::RectangleShape parametreButton;
    sf::RectangleShape quitButton;
    sf::Text playText;
    sf::Text parametreText;
    sf::Text quitText;

    void setupMenu() {
        int longueur_bouton = 200, hauteur_bouton = 50, espace_bouton = 60;
        int longeur = window.getSize().x, hauteur = window.getSize().y;

        playButton.setSize(sf::Vector2f(longueur_bouton, hauteur_bouton));
        playButton.setPosition((longeur - longueur_bouton) / 2, (hauteur - 3 * hauteur_bouton - 2 * espace_bouton) / 2);
        playButton.setFillColor(sf::Color::Blue);
        playText.setFont(font);
        playText.setString("Jouer");
        playText.setCharacterSize(30);
        playText.setFillColor(sf::Color::White);
        adjustTextToButton(playText, playButton);

        parametreButton.setSize(sf::Vector2f(longueur_bouton, hauteur_bouton));
        parametreButton.setPosition(playButton.getPosition().x, playButton.getPosition().y + hauteur_bouton + espace_bouton);
        parametreButton.setFillColor(sf::Color::Yellow);
        parametreText.setFont(font);
        parametreText.setString("Option");
        parametreText.setCharacterSize(30);
        parametreText.setFillColor(sf::Color::White);
        adjustTextToButton(parametreText, parametreButton);

        quitButton.setSize(sf::Vector2f(longueur_bouton, hauteur_bouton));
        quitButton.setPosition(parametreButton.getPosition().x, parametreButton.getPosition().y + hauteur_bouton + espace_bouton);
        quitButton.setFillColor(sf::Color::Red);
        quitText.setFont(font);
        quitText.setString("Quitter");
        quitText.setCharacterSize(30);
        quitText.setFillColor(sf::Color::White);
        adjustTextToButton(quitText, quitButton);
    }

    void render() {
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        window.draw(playButton);
        window.draw(playText);
        window.draw(parametreButton);
        window.draw(parametreText);
        window.draw(quitButton);
        window.draw(quitText);
        window.display();
    }
};