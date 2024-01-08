#include <filesystem>
#include <iostream>
#include "Game.h"
#include <windows.h>

Game::Game(GameState &gameState, sf::RenderWindow &window) :
    window(window),
    player1(5.0f, {20.0f, 100.0f}, 1, gameState.player1),
    player2(5.0f, {20.0f, 100.0f}, 2, gameState.player2),
    ball(3.0f, {20.0f, 20.0f}, gameState.ball),
    gameState(gameState) {
    this->window.setFramerateLimit(150);
    this->initializeScore();
}

void Game::update() {
    sf::Vector2u globalBounds = window.getSize();
    this->player1.update(globalBounds);
    this->player2.update(globalBounds);
    this->ball.update(globalBounds, this->player1, this->player2);
    this->drawScore(window);
}

void Game::draw() {
    this->player1.draw(this->window);
    this->player2.draw(this->window);
    this->ball.draw(this->window);
}

void Game::keyHandler(sf::Keyboard::Key &keyPressed, bool pressed) {
    this->player1.setDirection(Game::translateDirection(keyPressed, 1), pressed);
    this->player2.setDirection(Game::translateDirection(keyPressed, 2), pressed);
}

Direction Game::translateDirection(sf::Keyboard::Key &keyPressed, int playerIndex) {
    if (playerIndex == 1) {
        if (keyPressed == sf::Keyboard::W) return UP;
        if (keyPressed == sf::Keyboard::S) return DOWN;
    }
    if (playerIndex == 2) {
        if (keyPressed == sf::Keyboard::Up) return UP;
        if (keyPressed == sf::Keyboard::Down) return DOWN;
    }
    return INVALID_DIRECTION;
}

int Game::getPlayer1Score() const {
    return this->gameState.player1.score ;
}
int Game::getPlayer2Score() const {
    return this->gameState.player2.score;
}

bool Game::endGame(int endScore) {
    const std::string& winnerMessage = (this->gameState.player1.score == endScore) ? "Player2 wins!" :
                                       (this->gameState.player2.score == endScore) ? "Player1 wins!" : "";

    if (!winnerMessage.empty()) {
        MessageBoxA(NULL, winnerMessage.c_str(), "EndGame", MB_OK );
        return true;
    }
    return false;
}

void Game::initializeScore(){
    this->player1ScoreText.setFont(font);
    this->player1ScoreText.setCharacterSize(24);
    this->player1ScoreText.setFillColor(sf::Color::White);

    this->player2ScoreText.setFont(font);
    this->player2ScoreText.setCharacterSize(24);
    this->player2ScoreText.setFillColor(sf::Color::White);
}

void Game::drawScore(sf::RenderWindow &window){
    std::filesystem::path path = std::filesystem::current_path();
    if(!font.loadFromFile(path.string() + "\\font\\arial.ttf"))
    {
        std::cout << "can't load font" << std::endl;
    }
    this->player1ScoreText.setString("Player 1: " + std::to_string(getPlayer1Score()));
    this->player2ScoreText.setString("Player 2: " + std::to_string(getPlayer2Score()));

    this->player1ScoreText.setPosition(0,0);
    this->player2ScoreText.setPosition(window.getSize().x - player2ScoreText.getLocalBounds().width - 10, 0);

    this->window.draw(player1ScoreText);
    this->window.draw(player2ScoreText);
}
