#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <filesystem>
#include <iostream>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text buttonText;
    sf::Font font;
public:

    Button(float x, float y, float width, float height, const std::string& text) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::White);

        std::filesystem::path path = std::filesystem::current_path();
        if(!font.loadFromFile(path.string() + "\\font\\arial.ttf"))
        {
            std::cout << "can't load font" << std::endl;
        }
        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = buttonText.getLocalBounds();
        buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        buttonText.setPosition(x + width / 2.0f, y + height / 2.0f);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(buttonText);
    }

    bool checkClick(const sf::Vector2f& mousePosition) {
        return shape.getGlobalBounds().contains(mousePosition);
    }
};