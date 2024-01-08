#pragma once

#include "Button.h"
#include "../enums/MultiPlayerGameMode.h"

class ModeSelect {
private:
    Button createGameButton;
    Button joinGameButton;
    Button exitButton;
public:
    ModeSelect();

    void draw(sf::RenderWindow &window);
    void displayInfo(std::string pText, sf::RenderWindow &window);

    MultiPlayerGameMode handleMenu(sf::RenderWindow &window, bool secondTime);
    MultiPlayerGameMode checkButtonClick(sf::Event::MouseButtonEvent mouseButtonEvent);
};