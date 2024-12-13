//Musica
#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Musica {
private:
    sf::Music introMusic;
    sf::Music gameMusic;
    sf::Music clickSound;
    sf::Music gameOverMusic;

public:
    Musica() = default;

    bool cargarMusica(const std::string& introPath, const std::string& gamePath, const std::string& clickPath, const std::string& gameOverPath) {
        if (!introMusic.openFromFile(introPath) ||
            !gameMusic.openFromFile(gamePath) ||
            !clickSound.openFromFile(clickPath) ||
            !gameOverMusic.openFromFile(gameOverPath)) {
            return false;
        }
        introMusic.setLoop(true);
        gameMusic.setLoop(true);
        return true;
    }
 
    void reproducirIntro() { introMusic.play(); }
    void detenerIntro() { introMusic.stop(); }

    void reproducirJuego() { gameMusic.play(); }
    void detenerJuego() { gameMusic.stop(); }

    void reproducirClick() { clickSound.play(); }

    void reproducirGameOver() { gameOverMusic.play(); }
    void detenerGameOver() { gameOverMusic.stop(); }
};
