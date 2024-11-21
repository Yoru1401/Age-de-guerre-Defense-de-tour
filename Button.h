#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#ifndef BUTTON_H
#define BUTTON_H

void adjustTextToButton(sf::Text &text, const sf::Shape &button) {
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





#endif //BUTTON_H
