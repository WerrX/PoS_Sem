#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

struct PlayerState {
    bool up;
    bool down;
    sf::Vector2f position;
    int score;
};

class Paddle : public Entity {
private:
    int index;
    PlayerState &playerState;

public:
    Paddle(float speed, sf::Vector2f size, int index, PlayerState &playerState);

    void setCollisionDirections
        (sf::Vector2f &nextPosition, sf::Vector2u &globalBounds, std::vector<Direction> &collidedDirections)
        override;
    void draw(sf::RenderWindow &window) override;

    sf::Vector2f getNextPosition() override;
    sf::Vector2f getPosition() override;

    int getIndex() const;

    void setDirection(Direction direction, bool pressed);
    void update(sf::Vector2u &globalBounds);

    void setScore();
};