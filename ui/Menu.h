#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "../enums/MenuState.h"

class Menu {
private:
    Button singlePlayerButton;
    Button multiPlayerButton;
    Button exitButton;
public:
    Menu();

    MenuState handleMenu(sf::RenderWindow &window);
    MenuState checkButtonClick(sf::Event::MouseButtonEvent mouseButtonEvent);

    void draw(sf::RenderWindow& window);
};