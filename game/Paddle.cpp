#include "Paddle.h"

Paddle::Paddle(float speed, sf::Vector2f size, int index, PlayerState &playerState) :
    Entity(speed, size, playerState.position), index(index), playerState(playerState) {}

void Paddle::setDirection(Direction direction, bool pressed) {
    if (pressed) {
        if (direction == UP) this->playerState.up = true;
        else if (direction == DOWN) this->playerState.down = true;
    } else {
        if (direction == UP) this->playerState.up = false;
        else if (direction == DOWN) this->playerState.down = false;
    }
}


void Paddle::update(sf::Vector2u &globalBounds) {
    sf::Vector2f nextPosition = this->getNextPosition();
    std::vector<Direction> collidedDirections;
    this->setCollisionDirections(nextPosition, globalBounds, collidedDirections);
    if (!collidedDirections.empty()) {
        for (const auto& direction : collidedDirections) {
            this->setDirection(direction, false);
        }
        nextPosition = this->getPosition();
    }
    this->playerState.position = nextPosition;
    this->setPosition(nextPosition);
}

//zmena---------------------------------------------------
void Paddle::setScore(){
    this->playerState.score += 1;
}

void Paddle::setCollisionDirections(
        sf::Vector2f &nextPosition, sf::Vector2u &globalBounds, std::vector<Direction> &collidedDirections
        ) {
    if (globalBounds.y <= (nextPosition.y + this->getShape().getSize().y)) collidedDirections.push_back(DOWN);
    else if (0 >= nextPosition.y) collidedDirections.push_back(UP);
}

sf::Vector2f Paddle::getNextPosition() {
    if (this->playerState.up) {
        return {this->getPosition().x, this->getPosition().y - this->getSpeed()};
    } else if (this->playerState.down) {
        return {this->getPosition().x, this->getPosition().y + this->getSpeed()};
    }
    return {this->getPosition().x, this->getPosition().y};
}

sf::Vector2f Paddle::getPosition() {
    return this->playerState.position;
}

void Paddle::draw(sf::RenderWindow &window) {
    window.draw(this->getShape());
}

int Paddle::getIndex() const {
    return this->index;


}
