#pragma once

#include "Game.h"
#include "../enums/MultiPlayerGameMode.h"
#include "../networking/NetworkManager.h"
#include <iostream>
#include <thread>
#include "../ui/IpDialog.h"
#include <filesystem>


class Multiplayer : public Game {
private:
    NetworkManager &networkManager;
    MultiPlayerGameMode gameMode;
public:
    Multiplayer(GameState &gameState, NetworkManager &networkManager, sf::RenderWindow &window);

    void start() override;

    static void* retrieveThread(void* arg);

    void setPlayerState(PlayerState state);
    void keyHandler(sf::Keyboard::Key &keyPressed, bool pressed, bool send);
    void displayInfo(std::string pText);
    void sendPlayerState();
    void closeConnections();

    bool syncBallState();
    sf::Keyboard::Key filterKeyCode(sf::Keyboard::Key &keyPressed);
    bool initializeConnection(MultiPlayerGameMode mode);
};