#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include "Button.h"

#ifndef MENU_H
#define MENU_H
/*class Menu {
    public:
    Menu();
    void display(sf::RenderWindow& window);

    private:


};
void drawMenu(sf::RenderWindow& window) {
    // Dimensions du menu
    sf::RectangleShape menu(sf::Vector2f(window.getSize().x/2.5, 200));
    menu.setFillColor(sf::Color(0, 0, 250)); // Couleur du menu
    menu.setPosition(0, window.getSize().y - 200); // En bas à gauche de l'écran

    // Options de menu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Assurez-vous d'avoir un fichier arial.ttf dans le même répertoire
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
        return;
    }
    sf::RectangleShape boutonArcher(sf::Vector2f(200, 50));
    sf::RectangleShape boutonMage(sf::Vector2f(200, 50));
    sf::RectangleShape boutonPerceArmure(sf::Vector2f(200, 50));

    // Position des boutons
    boutonArcher.setPosition(50, 500);
    boutonMage.setPosition(300, 500);
    boutonPerceArmure.setPosition(550, 500);

    // Couleurs des boutons
    boutonArcher.setFillColor(sf::Color(150, 150, 255));
    boutonMage.setFillColor(sf::Color(255, 150, 150));
    boutonPerceArmure.setFillColor(sf::Color(150, 255, 150));

    // Textes des boutons
    sf::Font font;
    sf::Text textArcher("Tour d'archer", font, 20);
    sf::Text textMage("Tour de mage", font, 20);
    sf::Text textPerceArmure("Tour perce-armure", font, 20);


    adjustTextToButton(textArcher, boutonArcher);
    adjustTextToButton(textMage, boutonMage);
    adjustTextToButton(textPerceArmure, boutonPerceArmure);



    window.draw(menu);
    window.draw(boutonArcher);
    window.draw(boutonMage);
    window.draw(boutonPerceArmure);
    window.draw(textArcher);
    window.draw(textMage);
    window.draw(textPerceArmure);


}*/

// Classe pour gérer un bouton
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    // Constructeur
    Button(float x, float y, float width, float height, const sf::Font& font, const std::string& label, sf::Color bgColor, sf::Color textColor) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(bgColor);

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(20);
        text.setFillColor(textColor);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            x + (width - textBounds.width) / 2,
            y + (height - textBounds.height) / 2 - 5
        );
    }

    // Dessiner le bouton
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(text);
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
    // Constructeur
    Menu() : isOpen(false) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Erreur : Impossible de charger la police 'arial.ttf'" << std::endl;
            exit(-1);
        }

        buttons[0] = new Button(100, 200, 200, 50, font, "Tour d'archer", sf::Color(150, 150, 255), sf::Color::White);
        buttons[1] = new Button(100, 300, 200, 50, font, "Tour de mage", sf::Color(255, 150, 150), sf::Color::White);
        buttons[2] = new Button(100, 400, 200, 50, font, "Tour perce-armure", sf::Color(150, 255, 150), sf::Color::White);
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
    void handleClick(float mouseX, float mouseY) const {
        if (isOpen) {
            if (buttons[0]->isClicked(mouseX, mouseY)) {
                std::cout << "Bouton 'Tour d'archer' cliqué !" << std::endl;
            }
            if (buttons[1]->isClicked(mouseX, mouseY)) {
                std::cout << "Bouton 'Tour de mage' cliqué !" << std::endl;
            }
            if (buttons[2]->isClicked(mouseX, mouseY)) {
                std::cout << "Bouton 'Tour perce-armure' cliqué !" << std::endl;
            }
        }
    }

    // Vérifier si le menu est ouvert
    bool isMenuOpen() const {
        return isOpen;
    }
};

#endif
