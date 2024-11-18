
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Ennemis.h"
#include <iostream>
#include <cstdlib>

void adjustTextToButton(sf::Text &text, const sf::Sprite &button) {
    const float padding = 10.0f; // Marge entre le texte et les bords du bouton

    // Dimensions du bouton
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    // Ajustement de la taille du texte
    while (true) {
        sf::FloatRect textBounds = text.getGlobalBounds();

        // Vérifie si le texte dépasse les limites du bouton
        if (textBounds.width + padding < buttonBounds.width &&
            textBounds.height + padding < buttonBounds.height) {
            break;
            }

        // Réduit la taille de la police si le texte est trop grand
        text.setCharacterSize(text.getCharacterSize() - 1);

        if (text.getCharacterSize() <= 5) { // Éviter une taille trop petite
            break;
        }
    }

    // Centrage du texte dans le bouton
    text.setPosition(
        buttonBounds.left + (buttonBounds.width / 2.0f) - (text.getGlobalBounds().width / 2.0f),
        buttonBounds.top + (buttonBounds.height / 2.0f) - (text.getGlobalBounds().height / 1.8f)
    );
}

void CréerBouton(int Xsize, int Ysize, int forme, int posX, int posY) {}

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Création de la fenêtre en mode plein écran
    sf::RenderWindow window(desktop, "Bouton avec Image (Plein écran)", sf::Style::Fullscreen);

    // Chargement de la texture pour le bouton
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("PlaceForTower2.png")) { // Remplacez par le chemin de votre image
        std::cerr << "Erreur : Impossible de charger l'image du bouton\n";
        return -1;
    }

    // Création du sprite pour représenter le bouton
    sf::Sprite button(buttonTexture);
    button.setPosition(300, 250); // Position initiale du bouton

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police\n";
        return -1;
    }

    // Texte à afficher sur le bouton
    sf::Text buttonText("Cliquez-moi !", font);
    buttonText.setFillColor(sf::Color::White);

    adjustTextToButton(buttonText, button);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gestion du clic sur le bouton
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Bouton cliqué !" << std::endl;

                }
            }
        }


        window.clear();
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}