#include <filesystem>
#include "IpDialog.h"

IpDialog::IpDialog() :
    window(sf::VideoMode(500, 200), "Host IP", sf::Style::Close),
    yesButton(300, 100, 100, 50, "Connect"),
    noButton(100, 100, 100, 50, "Back") {
    this->window.setFramerateLimit(150);
}

std::string IpDialog::getIp() {
    sf::Font font;
    std::filesystem::path path = std::filesystem::current_path();
    if(!font.loadFromFile(path.string() + "\\font\\arial.ttf"))
    {
        std::cout << "can'text load font" << std::endl;
    }
    sf::Text text;
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    std::string ipString = "Type host IP: ";
    bool templateString = true;
    text.setString(ipString);

    while (this->window.isOpen()) {
        sf::Event event;

        while (this->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->window.close();
            }
            if (event.type == sf::Event::TextEntered){
                char enteredChar = static_cast<char>(event.text.unicode);
                if (enteredChar == 8 && !ipString.empty()) {
                    ipString.pop_back();
                }
                if (!((enteredChar >= '1' && enteredChar <= '9') || enteredChar == '.')) continue;
                if (templateString) {
                    ipString = static_cast<char>(event.text.unicode);
                    templateString = false;
                } else {
                    ipString += static_cast<char>(event.text.unicode);
                }
            }  else if (event.type == sf::Event::MouseButtonReleased) {
                YesNo clickEventType = checkButtonClick(event.mouseButton);
                if (clickEventType == INVALID_YES_NO) continue;
                this->window.close();
                if (clickEventType == YES) return ipString;
                else if (clickEventType == NO) return "";
            }
        }

        text.setString(ipString);
        this->window.clear(sf::Color::Black);
        this->window.draw(text);
        this->draw();
        this->window.display();
    }
    return "";
}

YesNo IpDialog::checkButtonClick(sf::Event::MouseButtonEvent mouseButtonEvent) {
    sf::Vector2f mousePosition = {static_cast<float>(mouseButtonEvent.x),static_cast<float>(mouseButtonEvent.y)};
    if (this->yesButton.checkClick(mousePosition)) return YES;
    if (this->noButton.checkClick(mousePosition)) return NO;
    return INVALID_YES_NO;
}

void IpDialog::draw() {
    this->yesButton.draw(this->window);
    this->noButton.draw(this->window);
}
