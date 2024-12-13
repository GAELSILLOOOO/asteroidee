#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Personaje.hpp>
#include <Fondo.hpp>
#include <Meteoro.hpp>
#include <Musica.hpp>
#include <Texto.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    std::srand(static_cast<unsigned>(std::time(0)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spaceship");
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Fondo
    Fondo fondo("assets/images/menu.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);
    Fondo menuFondo("assets/images/Designer_30_.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Carga de fuentes
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/space.ttf")) {
        return -1;
    }

    // Textos
    Texto rectText(font, "JUGAR", 40, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);
    Texto meteorCounterText(font, "Meteoritos: 0", 30, sf::Color::White, 170, 30); // Posicionado en la esquina superior izquierda
    Texto gameOverText(font, "GAME OVER", 80, sf::Color::Red, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);
    Texto gameOverInstruction(font, "Click aqui para regresar al inicio", 30, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
    Texto gameOverCounterText(font, "", 40, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50);

    // Música
    Musica musica;
    if (!musica.cargarMusica("assets/music/intro.ogg", "assets/music/musica.ogg", "assets/music/click.ogg", "assets/music/gameover.ogg")) {
        return -1;
    }

    musica.reproducirIntro();

    // Personajes
    Personaje nave("assets/images/nave.png", 400, WINDOW_HEIGHT - 200);
    nave.setScale(0.5f, 0.5f);

    // Meteoros
    Meteoro meteoro("assets/images/a.png", std::rand() % (WINDOW_WIDTH - 100) + 50, -100, 0.1f, 0.1f);

    bool inMainMenu = true;
    bool gameOver = false;

    float backgroundSpeed = 400.0f;
    float naveSpeed = 300.0f;
    float meteoroSpeed = 1500.0f;
    int meteorCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameOver && event.type == sf::Event::MouseButtonPressed) {
                musica.detenerGameOver();
                inMainMenu = true;
                gameOver = false;
                meteorCount = 0;
                meteoro.resetPosition(WINDOW_WIDTH, -100);
                nave.resetPosition(400, WINDOW_HEIGHT - 200);
                musica.reproducirIntro();
            }

            if (inMainMenu && !gameOver) {
                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (rectText.getBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        rectText.setContenido("JUGAR");
                        rectText = Texto(font, "JUGAR", 40, sf::Color::Red, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                    } else {
                        rectText = Texto(font, "JUGAR", 40, sf::Color::White, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (rectText.getBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        musica.reproducirClick();
                        musica.detenerIntro();
                        musica.reproducirJuego();
                        inMainMenu = false;
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (!inMainMenu && !gameOver) {
            fondo.mover(backgroundSpeed, deltaTime);

            sf::Vector2f navePos = nave.getPosition();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && navePos.y > 0) {
                nave.mover(0, -naveSpeed * deltaTime);
            } else if (navePos.y <= 0) {
                musica.detenerJuego();
                musica.reproducirGameOver();
                gameOver = true;
                gameOverCounterText.setContenido("Meteoritos esquivados: " + std::to_string(meteorCount));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && navePos.y + nave.getBounds().height < WINDOW_HEIGHT) {
                nave.mover(0, naveSpeed * deltaTime);
            } else if (navePos.y + nave.getBounds().height >= WINDOW_HEIGHT) {
                musica.detenerJuego();
                musica.reproducirGameOver();
                gameOver = true;
                gameOverCounterText.setContenido("Meteoritos esquivados: " + std::to_string(meteorCount));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && navePos.x > 0) {
                nave.mover(-naveSpeed * deltaTime, 0);
            } else if (navePos.x <= 0) {
                musica.detenerJuego();
                musica.reproducirGameOver();
                gameOver = true;
                gameOverCounterText.setContenido("Meteoritos esquivados: " + std::to_string(meteorCount));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && navePos.x + nave.getBounds().width < WINDOW_WIDTH) {
                nave.mover(naveSpeed * deltaTime, 0);
            } else if (navePos.x + nave.getBounds().width >= WINDOW_WIDTH) {
                musica.detenerJuego();
                musica.reproducirGameOver();
                gameOver = true;
                gameOverCounterText.setContenido("Meteoritos esquivados: " + std::to_string(meteorCount));
            }

            meteoro.mover(0, meteoroSpeed * deltaTime);

            if (meteoro.getPosition().y > WINDOW_HEIGHT) {
                meteorCount++;
                meteoro.resetPosition(WINDOW_WIDTH, -100);
            }

            if (nave.getBounds().intersects(meteoro.getBounds())) {
                musica.detenerJuego();
                musica.reproducirGameOver();
                gameOver = true;

                gameOverCounterText.setContenido("Meteoritos esquivados: " + std::to_string(meteorCount));
            }

            meteorCounterText.setContenido("Meteoritos: " + std::to_string(meteorCount));
        }

        window.clear();

        if (inMainMenu) {
            menuFondo.dibujar(window);
            rectText.dibujar(window);
        } else if (gameOver) {
            gameOverText.dibujar(window);
            gameOverInstruction.dibujar(window);
            gameOverCounterText.dibujar(window);
        } else {
            fondo.dibujar(window);
            nave.dibujar(window);
            meteoro.dibujar(window);
            meteorCounterText.dibujar(window);
        }

        window.display();
    }

    return 0;
}