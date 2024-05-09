#include "ConfigSimulation.hpp"

ConfigSimulation::ConfigSimulation(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<System<double>> system,
                                   Scene &p_selectedScene)
    : window(window), system(system), selectedScene(p_selectedScene),
      textInputs({
          TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                    sf::Color::Red, sf::Color::Black,
                    "Ball start Angle (radians)",
                    "1"), // theta
          TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                    sf::Color::Red, sf::Color::Black, "Ball start y", "0"), // y
          TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                    sf::Color::Red, sf::Color::Black, "Pool length",
                    "1000"), // l
          TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                    sf::Color::Red, sf::Color::Black, "Start Radius",
                    "200"), // r1
          TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                    sf::Color::Red, sf::Color::Black, "End radius", "100") // r2
      }) {

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeComponents();
}
void ConfigSimulation::initializeComponents() {
    title.setFont(font);
    title.setString("Configure Simulation");
    title.setCharacterSize(window->getSize().x / 20);
    title.setFillColor(sf::Color::White);
    title.setPosition(
        window->getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

    titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50,
                                  title.getGlobalBounds().height + 50));
    titleBox.setFillColor(sf::Color(0, 147, 45));
    titleBox.setPosition(window->getSize().x / 2 -
                             titleBox.getGlobalBounds().width / 2,
                         title.getPosition().y);

    double inputBoxWidth = window->getSize().x / 3;
    double inputBoxHeight = window->getSize().y / 1.5;
    double inputBoxX = window->getSize().x / 2 - inputBoxWidth / 2;
    double inputBoxY = window->getSize().y / 5;

    inputBox.setSize(sf::Vector2f(inputBoxWidth, inputBoxHeight));
    inputBox.setFillColor(sf::Color(0, 147, 45));
    inputBox.setPosition(inputBoxX, inputBoxY);

    double startButtonWidth = inputBoxWidth / 2;
    double startButtonHeight = inputBoxHeight / 10;
    double startButtonX = window->getSize().x / 2 - startButtonWidth / 2;
    double startButtonY = inputBoxY + inputBoxHeight - startButtonHeight - 20;
    startButton.setSize(sf::Vector2f(startButtonWidth, startButtonHeight));
    startButton.setFillColor(sf::Color());
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
            sf::Vector2f(inputBoxX + 10, inputBoxY + 10 + i * 120));
        textInputs[i].setSize(sf::Vector2f(inputBoxWidth - 20, 120));
    }
}

void ConfigSimulation::draw() {
    window->clear(sf::Color::Black);
    window->draw(titleBox);
    window->draw(title);
    window->draw(inputBox);
    window->draw(startButton);
    for (auto &textInput : textInputs) {
        textInput.draw(*window);
    }
    window->draw(startButtonText);
    window->display();
}

void ConfigSimulation::processEvents() {
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

                system->updateParams(std::stod(textInputs[0].getText()),
                                     std::stod(textInputs[1].getText()),
                                     std::stod(textInputs[2].getText()),
                                     std::stod(textInputs[3].getText()),
                                     std::stod(textInputs[4].getText()));

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
