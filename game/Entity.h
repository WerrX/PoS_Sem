#pragma once

#include <SFML/Graphics.hpp>
#include "../enums/Direction.h"

class Entity {
private:
    sf::RectangleShape shape;
    float speed;
public:
    Entity(float speed, sf::Vector2f size, sf::Vector2f position);

    virtual void setCollisionDirections
      (sf::Vector2f &nextPosition, sf::Vector2u &globalBounds, std::vector<Direction> &collidedDirections) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    [[nodiscard]] virtual sf::Vector2f getNextPosition() = 0;
    virtual sf::Vector2f getPosition() = 0;

    void setPosition(sf::Vector2f position);
    float getSpeed();
    sf::RectangleShape getShape();

    virtual ~Entity() = default;
};
