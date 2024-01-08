#pragma once

#include <SFML/Graphics.hpp>
#include <pthread.h>
#include "Paddle.h"
#include "Ball.h"

struct GameState {
    PlayerState &player1;
    PlayerState &player2;
    BallState &ball;
};

class Game {
private:
    Ball ball;

    sf::Font font;
    sf::Text player1ScoreText;
    sf::Text player2ScoreText;
protected:
    Paddle player1;
    Paddle player2;
    sf::RenderWindow &window;
    GameState &gameState;
public:
    Game(GameState &gameState, sf::RenderWindow &window);

    virtual void start() = 0;
    void update();
    void draw();
    virtual void keyHandler(sf::Keyboard::Key &keyPressed, bool pressed);

    static Direction translateDirection(sf::Keyboard::Key &keyPressed, int playerIndex);

    int getPlayer1Score() const;
    int getPlayer2Score() const;

    void initializeScore();

    void drawScore(sf::RenderWindow &window);

    bool endGame(int endScore);
};