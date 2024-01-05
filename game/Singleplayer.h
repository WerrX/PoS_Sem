#pragma once

#include "Game.h"

class Singleplayer : public Game {
public:
    Singleplayer(GameState &gameState, sf::RenderWindow &window);

    void start() override;
};