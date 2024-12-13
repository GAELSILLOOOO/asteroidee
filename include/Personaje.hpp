// clase Personaje.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

class Personaje {
public:
    Personaje(const std::string& texturePath, float startX, float startY) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("No se pudo cargar la textura del personaje");
        }
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
    }

    void mover(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    void resetPosition(float startX, float startY) {
        sprite.setPosition(startX, startY);
    }

    void setScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};