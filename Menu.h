#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include "Button.h"
#include <vector>

#ifndef MENU_H
#define MENU_H
class Button {
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    // Constructeur
     Button(float x, float y, float width, float height, const std::string& textureFile, sf::Color bgColor) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
         shape.setFillColor(bgColor);



        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Erreur : Impossible de charger la texture '" << textureFile << "'" << std::endl;
            exit(-1); // Gestion d'erreur
        }

        sprite.setTexture(texture);

        // Ajuster et centrer le sprite dans le bouton
        adjustSpriteToButton(sprite, shape);
    }

    // Dessiner le bouton
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);   // Dessiner la forme
        window.draw(sprite);  // Dessiner le sprite
    }

    // Vérifier si un point est à l'intérieur du bouton (pour les clics)
    bool isClicked(float mouseX, float mouseY) const {
        return shape.getGlobalBounds().contains(mouseX, mouseY);
    }
};

// Classe pour gérer le menu
class Menu {
private:
    sf::Font font;
    Button* buttons[3];
    bool isOpen; // Indique si le menu est ouvert

public:
    enum SelectedButton { None, Archer, Mage, Armor };
    SelectedButton selected = None;

    // Constructeur
    Menu(float screenWidth, float screenHeight) : isOpen(false), selected(None) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Erreur : Impossible de charger la police 'arial.ttf'" << std::endl;
            exit(-1);
        }

        // Positionnement dynamique basé sur la taille de l'écran

        float yStart = screenHeight; // Commence au milieu de l'écran en Y

        buttons[0] = new Button(0, yStart - 150, 150, 150, "archer_level_1.png", sf::Color::Transparent);
        buttons[1] = new Button(150, yStart - 150, 150, 150, "wizard_level_1.png", sf::Color::Transparent);
        buttons[2] = new Button(300, yStart - 150, 150, 150, "knight_level_1.png", sf::Color::Transparent);
    }

    // Destructeur
    ~Menu() {
        for (int i = 0; i < 3; i++) {
            delete buttons[i];
        }
    }

    // Ouvrir ou fermer le menu
    void toggle() {
        isOpen = !isOpen;
    }

    // Dessiner le menu si ouvert
    void draw(sf::RenderWindow& window) const {
        if (isOpen) {
            for (int i = 0; i < 3; i++) {
                buttons[i]->draw(window);
            }
        }
    }

    // Gérer les clics si le menu est ouvert
    void handleClick(float mouseX, float mouseY) {
        if (isOpen) {
            if (buttons[0]->isClicked(mouseX, mouseY)) {
                selected = Archer;
                std::cout << "Tour d'Archer sélectionnée !" << std::endl;
            }
            if (buttons[1]->isClicked(mouseX, mouseY)) {
                selected = Mage;
                std::cout << "Tour de Mage sélectionnée !" << std::endl;
            }
            if (buttons[2]->isClicked(mouseX, mouseY)) {
                selected = Armor;
                std::cout << "Tour perce-armure sélectionnée !" << std::endl;
            }
        }
    }

    // Vérifier si le menu est ouvert
    bool isMenuOpen() const {
        return isOpen;
    }

    // Retourner le bouton sélectionné
    SelectedButton getSelectedButton() const {
        return selected;
    }
};

#endif
