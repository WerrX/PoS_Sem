#include "ModeSelect.h"

ModeSelect::ModeSelect() :
        createGameButton(410.0f, 150.0f, 200.0f, 50.0f, "Create Game"),
        joinGameButton(410.0f, 250.0f, 200.0f, 50.0f, "Find Game"),
        exitButton(410.0f, 350.0f, 200.0f, 50.0f, "Back") {}

MultiPlayerGameMode ModeSelect::handleMenu(sf::RenderWindow &window) {
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                MultiPlayerGameMode clickEventType = checkButtonClick(event.mouseButton);
                if (clickEventType == BACK) return BACK;
                if (clickEventType == INVALID_STATE) continue;
                return clickEventType;
            }
        }

        window.clear();

        draw(window);

        window.display();
    }
    return INVALID_STATE;
}

MultiPlayerGameMode ModeSelect::checkButtonClick(sf::Event::MouseButtonEvent mouseButtonEvent) {
    sf::Vector2f mousePosition = {static_cast<float>(mouseButtonEvent.x),static_cast<float>(mouseButtonEvent.y)};
    if (this->createGameButton.checkClick(mousePosition)) return CREATE;
    if (this->joinGameButton.checkClick(mousePosition)) return FIND;
    if (this->exitButton.checkClick(mousePosition)) return BACK;
    return INVALID_STATE;
}

void ModeSelect::draw(sf::RenderWindow &window) {
    this->createGameButton.draw(window);
    this->joinGameButton.draw(window);
    this->exitButton.draw(window);
}