#pragma once

#include <SFML/Graphics.hpp>

class Fondo {
public:
    Fondo(const std::string& texturePath, float windowWidth, float windowHeight) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("No se pudo cargar la textura del fondo");
        }

        sprite1.setTexture(texture);
        sprite2.setTexture(texture);

        float scaleX = windowWidth / texture.getSize().x;
        float scaleY = windowHeight / texture.getSize().y;

        sprite1.setScale(scaleX, scaleY);
        sprite2.setScale(scaleX, scaleY);

        sprite1.setPosition(0, 0);
        sprite2.setPosition(sprite1.getGlobalBounds().width, 0);
    }

    void mover(float speed, float deltaTime) {
        sprite1.move(-speed * deltaTime, 0);
        sprite2.move(-speed * deltaTime, 0);

        if (sprite1.getPosition().x + sprite1.getGlobalBounds().width < 0) {
            sprite1.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, 0);
        }
        if (sprite2.getPosition().x + sprite2.getGlobalBounds().width < 0) {
            sprite2.setPosition(sprite1.getPosition().x + sprite1.getGlobalBounds().width, 0);
        }
    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(sprite1);
        ventana.draw(sprite2);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
};
