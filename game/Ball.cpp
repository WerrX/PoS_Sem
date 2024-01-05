#include <iostream>
#include "Ball.h"

Ball::Ball(float speed, sf::Vector2f size, BallState &ballState) : Entity(speed, size, ballState.position), ballState(ballState) {}

void Ball::setDirection(Direction direction) {
    if (direction == UP) { this->ballState.up = true; this->ballState.down = false; }
    if (direction == RIGHT) { this->ballState.right = true; this->ballState.left = false; }
    if (direction == DOWN) { this->ballState.down = true; this->ballState.up = false; }
    if (direction == LEFT) { this->ballState.left = true; this->ballState.right = false; }
}

void Ball::update(sf::Vector2u &globalBounds, Paddle player, Paddle player1) {
    sf::Vector2f nextPosition = this->getNextPosition();
    std::vector<Direction> collidedDirections;
    this->setPlayerCollisionDirections(nextPosition, player);
    this->setPlayerCollisionDirections(nextPosition, player1);
    this->setCollisionDirections(nextPosition, globalBounds, collidedDirections);
    if (!collidedDirections.empty()) {
        for (const auto& direction : collidedDirections) {
            this->setDirection(direction);
            //zmena
            if (direction == RIGHT) player.setScore();
            if (direction == LEFT)player1.setScore();
        }
        nextPosition = this->getPosition();
    }
    this->ballState.position = nextPosition;
    this->setPosition(nextPosition);
}

void Ball::setPlayerCollisionDirections(sf::Vector2f &nextPosition, Paddle &player) {
    int playerIndex = player.getIndex();
    sf::Vector2f playerBounds = player.getPosition();
    sf::Vector2f playerSize = player.getShape().getSize();
    sf::Vector2f ballSize = this->getShape().getSize();
    if (playerIndex == 1 && playerBounds.x + playerSize.x >= nextPosition.x && playerBounds.y <= nextPosition.y + ballSize.y && playerBounds.y + playerSize.y >= nextPosition.y) {
        this->setDirection(RIGHT);
    }
    if (playerIndex == 2 && playerBounds.x <= nextPosition.x + ballSize.x && playerBounds.y <= nextPosition.y + ballSize.y && playerBounds.y + playerSize.y >= nextPosition.y) {
        this->setDirection(LEFT);
    }
}

void Ball::setCollisionDirections(
        sf::Vector2f &nextPosition, sf::Vector2u &globalBounds, std::vector<Direction> &collidedDirections
) {
    if (globalBounds.y <= (nextPosition.y + this->getShape().getSize().y)) collidedDirections.push_back(UP);
    if (0 >= nextPosition.x)collidedDirections.push_back(RIGHT);

    if (0 >= nextPosition.y) collidedDirections.push_back(DOWN);
    if (globalBounds.x <= (nextPosition.x + this->getShape().getSize().x))collidedDirections.push_back(LEFT);


}



sf::Vector2f Ball::getPosition() {
    return this->ballState.position;
}

sf::Vector2f Ball::getNextPosition() {
    sf::Vector2f nextPosition = this->getPosition();
    if (this->ballState.up) nextPosition.y = this->getPosition().y - this->getSpeed();
    if (this->ballState.down) nextPosition.y = this->getPosition().y + this->getSpeed();
    if (this->ballState.left) nextPosition.x = this->getPosition().x - this->getSpeed();
    if (this->ballState.right) nextPosition.x = this->getPosition().x + this->getSpeed();
    return nextPosition;
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(this->getShape());
}