#include <SFML/Audio.hpp> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

int main() {
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    std::srand(static_cast<unsigned>(std::time(0)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spaceship");
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Carga de fondos
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/Designer_30_.jpg")) {
        return -1;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x,
                        static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y);

    // Carga de fuentes y textos
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/space.ttf")) {
        return -1;
    }

    sf::Text rectText("JUGAR", font, 60);
    rectText.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = rectText.getLocalBounds();
    rectText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    rectText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    sf::Text meteorCounterText("", font, 30); // Texto inicial vacío
    meteorCounterText.setFillColor(sf::Color::White);
    meteorCounterText.setPosition(10, 10);

    int meteorCount = 0; // Contador de meteoritos

    // Carga de música
    sf::Music Music;
    if (!Music.openFromFile("assets/music/intro.ogg")) {
        return -1;
    }
    Music.setLoop(true);
    Music.play();

    sf::Music secondMenuMusic;
    if (!secondMenuMusic.openFromFile("assets/music/musica.ogg")) {
        return -1;
    }

    sf::Music click;
    if (!click.openFromFile("assets/music/click.ogg")) {
        return -1;
    }

    // Música para Game Over
    sf::Music gameOverMusic;
    if (!gameOverMusic.openFromFile("assets/music/gameover.ogg")) {
        return -1;
    }

    // Carga de fondos para el segundo menú
    sf::Texture secondMenuBackgroundTexture;
    if (!secondMenuBackgroundTexture.loadFromFile("assets/images/menu.jpg")) {
        return -1;
    }
    sf::Sprite background1(secondMenuBackgroundTexture);
    sf::Sprite background2(secondMenuBackgroundTexture);
    float scaleX = static_cast<float>(WINDOW_WIDTH) / secondMenuBackgroundTexture.getSize().x;
    float scaleY = static_cast<float>(WINDOW_HEIGHT) / secondMenuBackgroundTexture.getSize().y;
    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
    background1.setPosition(0, 0);
    background2.setPosition(background1.getGlobalBounds().width, 0);

    // Personajes
    Personaje nave("assets/images/nave.png", 400, WINDOW_HEIGHT - 200);
    nave.setScale(0.5f, 0.5f);

    Personaje meteoro("assets/images/a.png", std::rand() % (WINDOW_WIDTH - 100) + 50, -100);
    meteoro.setScale(0.1f, 0.1f);

    bool inMainMenu = true;

    float backgroundSpeed = 400.0f;
    float naveSpeed = 300.0f;
    float meteoroSpeed = 1500.0f;

    sf::Text gameOverText("GAME OVER", font, 80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
    gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    sf::Text gameOverInstruction("Click en cualquier lugar para regresar al inicio", font, 30);
    gameOverInstruction.setFillColor(sf::Color::White);
    gameOverInstruction.setOrigin(gameOverInstruction.getLocalBounds().width / 2, gameOverInstruction.getLocalBounds().height / 2);
    gameOverInstruction.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);

    sf::Text gameOverCounterText("", font, 40);
    gameOverCounterText.setFillColor(sf::Color::White);

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameOver) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    gameOverMusic.stop();
                    gameOver = false;
                    inMainMenu = true;
                    Music.play();

                    meteorCount = 0; // Reiniciar contador
                    meteorCounterText.setString(""); // Texto vacío hasta que caiga el primer meteoro
                }
                continue;
            }

            if (inMainMenu) {
                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (rectText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        rectText.setFillColor(sf::Color::Red);
                    } else {
                        rectText.setFillColor(sf::Color::White);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (rectText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        click.play();
                        Music.stop();
                        secondMenuMusic.play();
                        secondMenuMusic.setLoop(true);
                        inMainMenu = false;

                        nave.resetPosition(400, WINDOW_HEIGHT - 200);
                        meteoro.resetPosition(std::rand() % (WINDOW_WIDTH - 100) + 50, -100);
                        background1.setPosition(0, 0);
                        background2.setPosition(background1.getGlobalBounds().width, 0);
                    }
                }
            }
        }

        if (gameOver) {
            if (gameOverMusic.getStatus() != sf::Music::Playing) {
                gameOverMusic.play();
            }

            window.clear();
            window.draw(gameOverText);
            window.draw(gameOverInstruction);
            window.draw(gameOverCounterText); // Dibuja el contador
            window.display();
            continue;
        }

        float deltaTime = clock.restart().asSeconds();

        if (!inMainMenu) {
            background1.move(-backgroundSpeed * deltaTime, 0);
            background2.move(-backgroundSpeed * deltaTime, 0);

            if (background1.getPosition().x + background1.getGlobalBounds().width < 0) {
                background1.setPosition(background2.getPosition().x + background2.getGlobalBounds().width, 0);
            }
            if (background2.getPosition().x + background2.getGlobalBounds().width < 0) {
                background2.setPosition(background1.getPosition().x + background1.getGlobalBounds().width, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) nave.mover(0, -naveSpeed * deltaTime);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) nave.mover(0, naveSpeed * deltaTime);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) nave.mover(-naveSpeed * deltaTime, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) nave.mover(naveSpeed * deltaTime, 0);

            if (nave.getPosition().x < 0 || nave.getPosition().x + nave.getBounds().width > WINDOW_WIDTH ||
                nave.getPosition().y < 0 || nave.getPosition().y + nave.getBounds().height > WINDOW_HEIGHT) {
                secondMenuMusic.stop();
                gameOver = true;

                // Actualiza el texto del contador para Game Over
                gameOverCounterText.setString("Meteoritos contados: " + std::to_string(meteorCount));
                gameOverCounterText.setOrigin(gameOverCounterText.getLocalBounds().width / 2, gameOverCounterText.getLocalBounds().height / 2);
                gameOverCounterText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50);
            }

            meteoro.mover(0, meteoroSpeed * deltaTime);

            if (nave.getBounds().intersects(meteoro.getBounds())) {
                secondMenuMusic.stop();
                gameOver = true;

                // Actualiza el texto del contador para Game Over
                gameOverCounterText.setString("Meteoritos esquivados: " + std::to_string(meteorCount));
                gameOverCounterText.setOrigin(gameOverCounterText.getLocalBounds().width / 2, gameOverCounterText.getLocalBounds().height / 2);
                gameOverCounterText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 5 + 50);
            }

            if (meteoro.getPosition().y > WINDOW_HEIGHT || meteoro.getPosition().x < -50 || meteoro.getPosition().x > WINDOW_WIDTH + 50) {
                meteorCount++; // Incrementar contador
                meteorCounterText.setString("Meteoritos: " + std::to_string(meteorCount)); // Mostrar texto
                meteoro.resetPosition(std::rand() % (WINDOW_WIDTH - 100) + 50, -100);
            }
        }

        window.clear();

        if (inMainMenu) {
            window.draw(background);
            window.draw(rectText);
        } else {
            window.draw(background1);
            window.draw(background2);
            nave.dibujar(window);
            meteoro.dibujar(window);
            window.draw(meteorCounterText);
        }

        window.display();
    }

    return 0;
}