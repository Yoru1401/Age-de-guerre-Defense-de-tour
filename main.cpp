
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Menu.h"
#include "Button.h"
#include <iostream>
#include <cstdlib>
#include <vector>


int main() {
    // Taille dynamique de la fenêtre (pleine écran)
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Menu Dynamique", sf::Style::Fullscreen);


    // Création du menu avec la taille d'écran
    Menu menu(desktop.width, desktop.height);

    // Chargement des textures pour les sprites
    sf::Texture textureArcher, textureMage, textureArmor, Tour;
    if (!textureArcher.loadFromFile("archer_level_1.png") ||
        !textureMage.loadFromFile("wizard_level_1.png") ||
        !textureArmor.loadFromFile("knight_level_1.png")||
        !Tour.loadFromFile("PlaceForTower2.png")){
        std::cerr << "Erreur : Impossible de charger les textures !" << std::endl;
        return -1;
    }

    // Création des sprites correspondants
    sf::Sprite spriteArcher(textureArcher);
    sf::Sprite spriteMage(textureMage);
    sf::Sprite spriteArmor(textureArmor);
    sf::Sprite Plac_Tour(Tour); 


    // Liste pour stocker les sprites placés
    std::vector<sf::Sprite> placedSprites;
    Plac_Tour.setPosition(200.0f, 150.0f);
    Plac_Tour.setScale(2.0f, 2.0f);

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

            // Placer un sprite sur clic gauche si un bouton a été sélectionné
            if (event.type == sf:: Event ::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                Menu::SelectedButton selected = menu.getSelectedButton();

                if (selected != Menu::None) {
                    // Vérifier si le sprite "Plac_Tour" a déjà une texture définie
                    if (Plac_Tour.getTexture() == &Tour) {
                        // Définir la texture en fonction du bouton sélectionné
                        if (selected == Menu::Archer) {
                            Plac_Tour.setTexture(textureArcher);
                        } else if (selected == Menu::Mage) {
                            Plac_Tour.setTexture(textureMage);
                        } else if (selected == Menu::Armor) {
                            Plac_Tour.setTexture(textureArmor);
                        }

                        // Ajouter le sprite dans la liste des sprites placés

                        placedSprites.push_back(Plac_Tour);

                        std::cout << "Tour placée avec succès.\n";
                    } else {
                        std::cout << "Une tour est déjà placée ici.\n";
                    }
                }
            }


        }

        // Affichage
        window.clear(sf::Color::Black);
        menu.draw(window);
        window.draw(Plac_Tour);
        window.display();

        // Dessiner les sprites placés
        for (const auto& sprite : placedSprites) {
            window.draw(sprite);
        }

        window.display();
    }

    return 0;
}


