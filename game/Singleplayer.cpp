#include "Singleplayer.h"

Singleplayer::Singleplayer(GameState &gameState, sf::RenderWindow &window) : Game(gameState, window) {}

void Singleplayer::start() {
    while (this->window.isOpen())
    {
        sf::Event event{};

        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) this->window.close();
            if (event.type == sf::Event::KeyPressed) keyHandler(event.key.code, true);
            if (event.type == sf::Event::KeyReleased) keyHandler(event.key.code, false);
        }

        this->window.clear();

        update();
        draw();

        this->window.display();
        if(endGame(1))return;
    }
}