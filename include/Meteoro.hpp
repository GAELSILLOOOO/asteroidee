//meteoro
#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <stdexcept>

class Meteoro {
public:
    Meteoro(const std::string& texturePath, float startX, float startY, float scaleX, float scaleY) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("No se pudo cargar la textura del meteoro");
        }

        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
        sprite.setScale(scaleX, scaleY);
    }

    void mover(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void resetPosition(float windowWidth, float startY) {
        sprite.setPosition(std::rand() % static_cast<int>(windowWidth - 100) + 50, startY);
    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
