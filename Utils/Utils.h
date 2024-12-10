#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <string>
#include <utility>

namespace su {

    class Sprite {
    public:
        enum class ShapeType {
            Rectangle,
            Circle,
            Convex
        };

        std::unique_ptr<sf::Shape> shape;

        // Constructeur avec texture et couleur optionnelles
        Sprite(const sf::Vector2f& position, const sf::Vector2f& size,
               ShapeType shapeType = ShapeType::Rectangle,
               const sf::Texture* texture = nullptr,
               const sf::Color& color = sf::Color::White)
            : texture(texture), color(color) {
            switch (shapeType) {
                case ShapeType::Rectangle:
                    shape = std::make_unique<sf::RectangleShape>(size);
                break;
                case ShapeType::Circle:
                    shape = std::make_unique<sf::CircleShape>(size.x / 2.f); // Rayon basé sur la largeur
                break;
                case ShapeType::Convex:
                    createDefaultConvexShape(size);
                break;
            }

            shape->setPosition(position);


            if (texture) {
                shape->setTexture(texture);
            } else {
                shape->setFillColor(color);
            }
        }

        void draw(sf::RenderWindow& window) const {
            window.draw(*shape);
        }

        sf::FloatRect getBounds() const {
            return shape->getGlobalBounds();
        }

        void setTexture(const sf::Texture* newTexture) {
            texture = newTexture;
            shape->setTexture(texture);
        }

        void setColor(const sf::Color& newColor) {
            color = newColor;
            shape->setFillColor(color);
        }

    private:
        const sf::Texture* texture;
        sf::Color color;

        // Création d'une forme convexe par défaut
        void createDefaultConvexShape(const sf::Vector2f& size) {
            auto convex = std::make_unique<sf::ConvexShape>(4);
            convex->setPoint(0, {0.f, 0.f});
            convex->setPoint(1, {size.x, 0.f});
            convex->setPoint(2, {size.x, size.y});
            convex->setPoint(3, {0.f, size.y});
            shape = std::move(convex);
        }
    };


    class Text {
    public:
        Text(const std::string& content, const sf::Vector2f& position, const sf::Color& color, const sf::Font& font)
            : content(content) {



            text.setString(content); // Utilisation du contenu passé en paramètre
            text.setFont(font);
            text.setCharacterSize(30);
            text.setFillColor(color);


            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

            text.setPosition(position);
        }

        void draw(sf::RenderWindow& window) const {
            window.draw(text);
        }

        sf::FloatRect getGlobalBounds() const {
            return text.getGlobalBounds();
        }

        void setPosition(const sf::Vector2f& position) {
            text.setPosition(position);
        }

    private:
        sf::Text text;
        std::string content;
    };


    class Button {
    public:
        // Constructeur avec texte optionnel
        explicit Button(Sprite  sprite,
               Text* text = nullptr,
               std::function<void()> action = nullptr)
            : sprite(std::move(sprite)), action(std::move(action)) {setText(text);}

        void draw(sf::RenderWindow& window) const {
            // Dessiner le sprite
            sprite.draw(window);
            // Dessiner le texte si présent
            if (text) {
                text->draw(window);
            }
        }

        void setAction(const std::function<void()>& newAction) {
            action = newAction;
        }

        void handleClick(const sf::Vector2<float> mousePosition) const {
            if (sprite.getBounds().contains(mousePosition)) {
                if (action) {
                    action();
                }
            }
        }

        void setText(Text* newText) {
            text = newText;
            if (text) {
                // Ajuster la position du texte au centre du bouton
                auto bounds = sprite.getBounds();
                text->setPosition({
                    bounds.left + bounds.width / 2.f,
                    bounds.top + bounds.height / 2.f
                });
            }
        }

    private:
        Sprite sprite;
        Text* text{}; // Texte optionnel
        std::function<void()> action;
    };
}