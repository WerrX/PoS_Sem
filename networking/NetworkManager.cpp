#include <cstring>
#include "NetworkManager.h"

NetworkManager::NetworkManager() : listener(), socket(), hostAddress() {
    this->sourceAddress = sf::IpAddress::getLocalAddress();
}

void NetworkManager::setHostAddress(sf::IpAddress &address) {
    this->hostAddress = address;
}

void NetworkManager::closeSocket() {
    this->socket.disconnect();
}

void NetworkManager::closeListener() {
    this->listener.close();
}

bool NetworkManager::startListening() {
    this->listener.listen(this->portNumber);
    if (this->listener.accept(this->socket) == sf::Socket::Done) {
        return true;
    }
    return false;
}

bool NetworkManager::connectToIpAddress() {
    sf::Socket::Status status = this->socket.connect(this->hostAddress, this->portNumber);
    std::cout << status;
    if (status == sf::Socket::Done) {
        return true;
    }
    return false;
}

sf::IpAddress NetworkManager::getSourceIpAddress() {
    return this->sourceAddress;
}

template<typename T>
std::optional<T> NetworkManager::retrieve() {
    T retrievedData{};

    std::size_t enumSize = sizeof(T);
    std::size_t received;

    char buffer[enumSize];
    if (this->socket.receive(buffer, enumSize, received) != sf::Socket::Done) {
        return std::nullopt;
    }

    std::memcpy(&retrievedData, buffer, enumSize);
    return retrievedData;
}
template std::optional<PlayerState> NetworkManager::retrieve<PlayerState>();
template std::optional<BallState> NetworkManager::retrieve<BallState>();

template<typename T>
bool NetworkManager::send(const T& data) {
    std::size_t dataSize = sizeof(T);
    char buffer[dataSize];
    std::memcpy(buffer, &data, dataSize);
    return (this->socket.send(buffer, dataSize) == sf::Socket::Done);
}
template bool NetworkManager::send<PlayerState>(const PlayerState&);
template bool NetworkManager::send<BallState>(const BallState&);