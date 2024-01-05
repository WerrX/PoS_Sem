#include "Menu.h"

Menu::Menu() :
        singlePlayerButton(410.0f, 150.0f, 200.0f, 50.0f, "Single Player"),
        multiPlayerButton(410.0f, 250.0f, 200.0f, 50.0f, "Multi Player"),
        exitButton(410.0f, 350.0f, 200.0f, 50.0f, "Exit") {}

MenuState Menu::handleMenu(sf::RenderWindow &window) {
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                MenuState clickEventType = checkButtonClick(event.mouseButton);
                if (clickEventType == INVALID) continue;
                return clickEventType;
            }
        }

        window.clear();

        draw(window);

        window.display();
    }
    return EXIT;
}

MenuState Menu::checkButtonClick(sf::Event::MouseButtonEvent mouseButtonEvent) {
    sf::Vector2f mousePosition = {static_cast<float>(mouseButtonEvent.x),static_cast<float>(mouseButtonEvent.y)};
    if (this->singlePlayerButton.checkClick(mousePosition)) return SINGLEPLAYER;
    if (this->multiPlayerButton.checkClick(mousePosition)) return MULTIPLAYER;
    if (this->exitButton.checkClick(mousePosition)) return EXIT;
    return INVALID;
}

void Menu::draw(sf::RenderWindow &window) {
    this->singlePlayerButton.draw(window);
    this->multiPlayerButton.draw(window);
    this->exitButton.draw(window);
}