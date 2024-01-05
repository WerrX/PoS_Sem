#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Paddle.h"

struct BallState {
    bool up;
    bool right;
    bool down;
    bool left;
    sf::Vector2f position;
};

class Ball : public Entity {
private:
    BallState &ballState;
public:
    Ball(float speed, sf::Vector2f size, BallState &ballState);

    void setCollisionDirections
        (sf::Vector2f &nextPosition, sf::Vector2u &globalBounds, std::vector<Direction> &collidedDirections) override;
    void draw(sf::RenderWindow& window) override;

    sf::Vector2f getNextPosition() override;
    sf::Vector2f getPosition() override;

    void setPlayerCollisionDirections(sf::Vector2f &nextPosition, Paddle &player);
    void setDirection(Direction direction);
    void update(sf::Vector2u &globalBounds, Paddle player, Paddle player1);
};
