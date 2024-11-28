#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#ifndef BUTTON_H
#define BUTTON_H

void adjustSpriteToButton(sf::Sprite& sprite, const sf::Shape& button, float padding = 10.0f) {
    // Dimensions du bouton
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    // Dimensions du sprite avant mise à l'échelle
    sf::FloatRect spriteBounds = sprite.getLocalBounds();

    // Vérifier que le sprite n'a pas de dimensions nulles
    if (spriteBounds.width > 0 && spriteBounds.height > 0) {
        // Calcul des facteurs d'échelle pour que le sprite englobe le bouton avec un padding
        float scaleX = (buttonBounds.width + padding * 2) / spriteBounds.width;
        float scaleY = (buttonBounds.height + padding * 2) / spriteBounds.height;

        // Appliquer l'échelle au sprite
        sprite.setScale(scaleX, scaleY);
    }

    // Centrer le sprite autour du bouton
    sprite.setPosition(
        buttonBounds.left - padding,
        buttonBounds.top - padding
    );
}

void adjustTextureToSprite(sf::Sprite& sprite, const sf::Sprite& button, float padding = 10.0f) {
    // Dimensions du bouton
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    // Dimensions du sprite avant mise à l'échelle
    sf::FloatRect spriteBounds = sprite.getLocalBounds();

    // Vérifier que le sprite n'a pas de dimensions nulles
    if (spriteBounds.width > 0 && spriteBounds.height > 0) {
        // Calcul des facteurs d'échelle pour que le sprite englobe le bouton avec un padding
        float scaleX = (buttonBounds.width + padding * 2) / spriteBounds.width;
        float scaleY = (buttonBounds.height + padding * 2) / spriteBounds.height;

        // Appliquer l'échelle au sprite
        sprite.setScale(scaleX, scaleY);
    }

    // Centrer le sprite autour du bouton
    sprite.setPosition(
        buttonBounds.left - padding,
        buttonBounds.top - padding
    );
}





#endif //BUTTON_H
