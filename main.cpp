
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Menu.h"
#include "Button.h"
#include <iostream>
#include <cstdlib>



void CréerBouton(int Xsize, int Ysize, int posX, int posY) {

}


int main() {

    sf::VideoMode mode(1920, 1080, 32);
    if (mode.isValid()) {
        std::cout << "Le mode vidéo n'est pas valide !" << std::endl;

    }
    sf::RenderWindow window(mode, "Menu déroulant", sf::Style::Fullscreen);



    /*bool showMenu = false; // Indicateur pour afficher ou cacher le menu

    while (window.isOpen()) {
        sf::Event event;

        // Gestion des événements
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    showMenu = true; // Afficher le menu au clic gauche
                }
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (boutonArcher.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Bouton 'Tour d'archer' cliqué !" << std::endl;
                }
                if (boutonMage.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Bouton 'Tour de mage' cliqué !" << std::endl;
                }
                if (boutonPerceArmure.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Bouton 'Tour perce-armure' cliqué !" << std::endl;
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    showMenu = false; // Cacher le menu avec Échap
                }
            }
        }

        // Effacer l'écran
        window.clear(sf::Color(50, 50, 50));

        // Afficher le menu si nécessaire
        if (showMenu) {
            drawMenu(window);
        }

        // Afficher le contenu
        window.display();

    }*/
    Menu menu;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Ouvrir/fermer le menu avec un clic droit
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    menu.toggle();
                }

                // Gérer les clics sur les boutons si le menu est ouvert
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    menu.handleClick(mousePos.x, mousePos.y);
                }
            }
        }

        // Affichage
        window.clear(sf::Color::Black);
        menu.draw(window);
        window.display();
    }

    return 0;
}


