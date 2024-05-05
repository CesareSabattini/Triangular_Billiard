#include "Menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window,
           std::shared_ptr<System<double>> system, Scene &p_selectedScene)
    : window(window), system(system), selectedScene(p_selectedScene),
      textInputs({TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            sf::Color::Red, sf::Color::Black, "1"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            sf::Color::Red, sf::Color::Black, "20"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            sf::Color::Red, sf::Color::Black, "0"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            sf::Color::Red, sf::Color::Black, "100"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            sf::Color::Red, sf::Color::Black, "50"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            sf::Color::Red, sf::Color::Black, "40")}) {

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeComponents();
}
void Menu::initializeComponents() {

    title.setFont(font);
    title.setString("Triangular Pool Simulation");
    title.setCharacterSize(window->getSize().x / 20);
    title.setFillColor(sf::Color::Red);
    title.setPosition(
        window->getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

    double inputBoxWidth = window->getSize().x / 2;
    double inputBoxHeight = window->getSize().y / 1.5;
    double inputBoxX = 10;
    double inputBoxY = window->getSize().y / 5;

    inputBox.setSize(sf::Vector2f(inputBoxWidth, inputBoxHeight));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setPosition(inputBoxX, inputBoxY);

    double startButtonWidth = inputBoxWidth / 2;
    double startButtonHeight = inputBoxHeight / 10;
    double startButtonX =
        inputBoxX + (inputBoxWidth / 2) - (startButtonWidth / 2);
    double startButtonY = inputBoxY + inputBoxHeight + 10;
    startButton.setSize(sf::Vector2f(startButtonWidth, startButtonHeight));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(startButtonX, startButtonY);

    startButtonText.setFont(font);
    startButtonText.setString("Start Simulation");
    startButtonText.setCharacterSize(20);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(startButtonX + startButtonWidth / 2 -
                                    startButtonText.getGlobalBounds().width / 2,
                                startButtonY + startButtonHeight / 2 -
                                    startButtonText.getGlobalBounds().height /
                                        2);

    for (int i = 0; i < textInputs.size(); i++) {
        textInputs[i].setPosition(
            sf::Vector2f(inputBoxX + 10, inputBoxY + 10 + i * 60));
        textInputs[i].setSize(sf::Vector2f(inputBoxWidth - 20, 50));
    }
}

void Menu::draw() {
    window->clear(sf::Color::Black);
    window->draw(title);
    window->draw(inputBox);
    window->draw(startButton);
    for (auto &textInput : textInputs) {
        textInput.draw(*window);
    }
    window->draw(startButtonText);
    window->display();
}

void Menu::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

            bool anyInputFocused = false;
            for (auto &textInput : textInputs) {
                if (textInput.inputBox.getGlobalBounds().contains(
                        mousePosition.x, mousePosition.y)) {
                    textInput.setFocus(true);
                    anyInputFocused = true;
                } else {
                    textInput.setFocus(false);
                }
            }

            if (startButton.getGlobalBounds().contains(mousePosition.x,
                                                       mousePosition.y)) {
                system = std::make_shared<System<double>>(
                    std::stod(textInputs[0].getText()),
                    std::stod(textInputs[1].getText()),
                    std::stod(textInputs[2].getText()),
                    std::stod(textInputs[3].getText()),
                    std::stod(textInputs[4].getText()),
                    std::stod(textInputs[5].getText()));

                system->simulate();
                selectedScene = Scene::SIMULATION;
            }

            if (!anyInputFocused) {
                for (auto &textInput : textInputs) {
                    textInput.setFocus(false);
                }
            }
        }

        for (auto &textInput : textInputs) {
            if (textInput.isFocused && event.type == sf::Event::TextEntered) {
                textInput.handleEvent(event);
            }
        }
    }
}
