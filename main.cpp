#include <random>
#include "ui/Menu.h"
#include "game/Singleplayer.h"
#include "ui/ModeSelect.h"
#include "game/Multiplayer.h"

bool getRandomBoolean() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(gen) == 1;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1020, 760), "Pong", sf::Style::Close);

    bool up = getRandomBoolean();
    bool left = getRandomBoolean();

    PlayerState player1 = {false, false, {10.0f, 200.0f},0};
    PlayerState player2 = {false, false, {990.0f, 200.0f},0};
    BallState ball = {up, !left, !up, left, {500.0f, 308.0f}};
    GameState gameState = {player1, player2, ball};

    Menu menu;


    bool exit = false;
    while (!exit) {
        MenuState menuState = menu.handleMenu(window);

        if (menuState == SINGLEPLAYER) {
            Singleplayer game(gameState, window);
            game.start();
        } else if (menuState == MULTIPLAYER) {
            NetworkManager networkManager;
            Multiplayer game(gameState, networkManager, window);

            bool connectionEstablished = false;
//            implemetacia unable to connect
//            bool alreadyTriedToConnect = false;
            while (!connectionEstablished) {
                ModeSelect modeSelect;
                MultiPlayerGameMode gameMode = modeSelect.handleMenu(window);

                if (gameMode == BACK) break;

                connectionEstablished = game.initializeConnection(gameMode);
//                alreadyTriedToConnect = true;
            }
            if (connectionEstablished) game.start();
        } else if (menuState == EXIT) {
            exit = true;
        }
    }

    return 0;
}