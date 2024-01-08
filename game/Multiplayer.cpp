#include "Multiplayer.h"

Multiplayer::Multiplayer(GameState &gameState, NetworkManager &networkManager, sf::RenderWindow &window) :
    Game(gameState, window),
    networkManager(networkManager),
    gameMode() {
}

void Multiplayer::start() {
    sf::Thread retrieveThread(&Multiplayer::retrieveThread, this);
    retrieveThread.launch();
    while (this->window.isOpen())
    {
        sf::Event event{};

        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) this->window.close();
            if (event.type == sf::Event::KeyPressed) keyHandler(event.key.code, true, true);
            if (event.type == sf::Event::KeyReleased) keyHandler(event.key.code, false, true);
        }

        this->window.clear();

        update();
        draw();

        this->window.display();
        if(endGame(1))return;
    }
}

void* Multiplayer::retrieveThread(void* arg) {
    Multiplayer* instance = (Multiplayer*) arg;
    while (instance->window.isOpen()) {
        std::optional<PlayerState> playerState = instance->networkManager.retrieve<PlayerState>();
        if (playerState.has_value()) {
            instance->setPlayerState(*playerState);
        }
    }
}

void Multiplayer::keyHandler(sf::Keyboard::Key &keyPressed, bool pressed, bool send) {
    if (keyPressed == sf::Keyboard::Unknown) return;
    sf::Keyboard::Key pressedKeyFiltered = this->filterKeyCode(keyPressed);
    Game::keyHandler(pressedKeyFiltered, pressed);
    if (!send) return;
    this->sendPlayerState();
}

void Multiplayer::setPlayerState(PlayerState playerState) {
    if (this->gameMode == CREATE) {
        this->gameState.player2 = playerState;
    } else if (this->gameMode == FIND) {
        this->gameState.player1 = playerState;
    }
}

void Multiplayer::sendPlayerState() {
    PlayerState playerState;
    if (this->gameMode == CREATE) {
        playerState = this->gameState.player1;
    } else if (this->gameMode == FIND) {
        playerState = this->gameState.player2;
    }
    this->networkManager.send(playerState);
}

sf::Keyboard::Key Multiplayer::filterKeyCode(sf::Keyboard::Key &keyPressed) {
    if (this->gameMode == CREATE) {
        if (keyPressed == sf::Keyboard::W) return sf::Keyboard::W;
        if (keyPressed == sf::Keyboard::S) return sf::Keyboard::S;
    }
    if (this->gameMode == FIND) {
        if (keyPressed == sf::Keyboard::Up) return sf::Keyboard::Up;
        if (keyPressed == sf::Keyboard::Down) return sf::Keyboard::Down;
    }
    return sf::Keyboard::Unknown;
}

bool Multiplayer::initializeConnection(MultiPlayerGameMode mode) {
    this->displayInfo("");
    bool connected = false;
    if (mode == CREATE) {
        this->displayInfo("Host IP: " + this->networkManager.getSourceIpAddress().toString());
        connected = this->networkManager.startListening();
    } else if (mode == FIND) {
        IpDialog ipDialog;
        std::string hostIp = ipDialog.getIp();
        if (!hostIp.empty()) {
            auto foundIpAddress = sf::IpAddress(hostIp);
            this->networkManager.setHostAddress(foundIpAddress);
            connected = this->networkManager.connectToIpAddress();
        }
    }
    if (!connected) {
        this->displayInfo("Unable to connect");
    } else {
        this->gameMode = mode;
    }
    return connected;
}

void Multiplayer::displayInfo(std::string pText) {
    sf::Text text;
    sf::Font font;
    std::filesystem::path path = std::filesystem::current_path();
    if(!font.loadFromFile(path.string() + "\\font\\arial.ttf"))
    {
        std::cout << "can't load font" << std::endl;
    }
    text.setFont(font);
    text.setString(pText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    this->window.draw(text);
    this->window.display();
}