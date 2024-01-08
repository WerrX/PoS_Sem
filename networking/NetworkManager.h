#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "SFML/Network.hpp"
#include <thread>
#include <iostream>
#include <optional>
#include "../enums/MultiPlayerGameMode.h"
#include "../game/Paddle.h"
#include "../game/Ball.h"

class NetworkManager {
private:
    sf::IpAddress sourceAddress;
    sf::IpAddress hostAddress;

    sf::TcpListener listener;
    sf::TcpSocket socket;

    int portNumber = 53462;
public:
    NetworkManager();

    void setHostAddress(sf::IpAddress &address);
    void closeSocket();
    void closeListener();

    bool startListening();
    bool connectToIpAddress();
    sf::IpAddress getSourceIpAddress();

    template<typename T>
    std::optional<T> retrieve();

    template<typename T>
    bool send(const T& data);

};