#pragma once

#include <SFML/Graphics.hpp>
#include <pthread.h>
#include "Paddle.h"
#include "Ball.h"

struct GameState {
    PlayerState &player1;
    PlayerState &player2;
    BallState &ball;
    pthread_mutex_t windowMutex;
};

class Game {
private:
    Ball ball;

    //int player1Score = 0;
    //int player2Score = 0;

    //zmena
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

//    virtual bool waitForGameStatus() = 0;

    void setPlayer1Score(int score);
    void setPlayer2Score(int score);

    int getPlayer1Score() const;
    int getPlayer2Score() const;

    void initlizeScore();

    void drawScore(sf::RenderWindow &window);
};