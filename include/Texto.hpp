//clase Texto 
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Texto {
public:
    Texto(const sf::Font& font, const std::string& contenido, unsigned int tamano, sf::Color color, float posX, float posY) {
        texto.setFont(font);
        texto.setString(contenido);
        texto.setCharacterSize(tamano);
        texto.setFillColor(color);
        texto.setPosition(posX, posY);
        texto.setOrigin(texto.getLocalBounds().width / 2, texto.getLocalBounds().height / 2);
    }

    void setContenido(const std::string& contenido) {
        texto.setString(contenido);
        texto.setOrigin(texto.getLocalBounds().width / 2, texto.getLocalBounds().height / 2);
    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(texto);
    }

    void setPosition(float x, float y) {
        texto.setPosition(x, y);
    }

    sf::FloatRect getBounds() const {
        return texto.getGlobalBounds();
    }

private:
    sf::Text texto;
};
