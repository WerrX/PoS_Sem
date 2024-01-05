#include "Entity.h"

Entity::Entity(float speed, sf::Vector2f size, sf::Vector2f position) : speed(speed) {
    this->shape.setSize(size);
    this->shape.setPosition(position);
    this->shape.setFillColor(sf::Color::White);
}

sf::RectangleShape Entity::getShape() {
    return this->shape;
}

float Entity::getSpeed() {
    return this->speed;
}

void Entity::setPosition(sf::Vector2f position) {
    this->shape.setPosition(position);
}