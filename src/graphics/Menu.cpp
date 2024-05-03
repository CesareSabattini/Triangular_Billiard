#include "Menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window,
           std::shared_ptr<System<double>> system)
    : window(window), system(system) {

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeComponents();
}
void Menu::initializeComponents() {

    title.setFont(font);
    title.setString("Triangular Pool Simulation");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::Red);
    title.setPosition(200, 50);

    inputBox.setSize(sf::Vector2f(300, 150));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setPosition(250, 150);

    startButton.setSize(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300, 320);

    startButtonText.setFont(font);
    startButtonText.setString("Start Simulation");
    startButtonText.setCharacterSize(20);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(310, 325);
}

void Menu::draw() {
    window->clear(sf::Color::Black);
    window->draw(title);
    window->draw(inputBox);
    window->draw(startButton);
    window->draw(startButtonText);
    window->display();
}

void Menu::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}
