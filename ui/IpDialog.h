#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "../enums/YesNo.h"

class IpDialog {
private:
    sf::RenderWindow window;
    Button yesButton;
    Button noButton;
public:
    IpDialog();

    void draw();

    YesNo checkButtonClick(sf::Event::MouseButtonEvent mouseButtonEvent);
    std::string getIp();
};