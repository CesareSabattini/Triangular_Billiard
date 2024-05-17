#include "ConfigSimulation.hpp"

ConfigSimulation::ConfigSimulation(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<System<double>> system,
                                   Scene &p_selectedScene,
                                   SimulationWindow &simulationWindow)
    : system(system), window(window), selectedScene(p_selectedScene),
      simulationWindow(simulationWindow),
      startButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                  AppStyle::Colors::darkGreen, AppStyle::Colors::darkGreen.Blue,
                  AppStyle::Colors::darkGreen.Black, AppStyle::Colors::cream,
                  font, "Start Simulation", 20),
      menuButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                 AppStyle::Colors::cream, AppStyle::Colors::cream.Blue,
                 AppStyle::Colors::cream.Black, AppStyle::Colors::bgCyan, font,
                 "Menu", 20),

      textInputs({TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Ball start Angle (radians)", "1"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Ball start y", "0"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Pool length", "1000"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Start Radius", "200"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "End radius", "100")}) {

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeComponents();
}
void ConfigSimulation::initializeComponents() {
    title.setFont(font);
    title.setString("Configure Simulation");
    title.setCharacterSize(window->getSize().x / 20);
    title.setFillColor(AppStyle::Colors::bgCyan);
    title.setPosition(
        window->getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

    titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50,
                                  title.getGlobalBounds().height + 50));
    titleBox.setFillColor(AppStyle::Colors::cream);
    titleBox.setPosition(window->getSize().x / 2 -
                             titleBox.getGlobalBounds().width / 2,
                         title.getPosition().y);

    double inputBoxWidth = window->getSize().x / 3;
    double inputBoxHeight = window->getSize().y / 1.5;
    double inputBoxX = window->getSize().x / 2 - inputBoxWidth / 2;
    double inputBoxY = window->getSize().y / 5;

    inputBox.setSize(sf::Vector2f(inputBoxWidth, inputBoxHeight));
    inputBox.setFillColor(AppStyle::Colors::opaqueBlack);
    inputBox.setPosition(inputBoxX, inputBoxY);

    double startButtonWidth = inputBoxWidth / 2;
    double startButtonHeight = inputBoxHeight / 10;
    float startButtonX = window->getSize().x / 2 - startButtonWidth / 2;
    float startButtonY = inputBoxY + inputBoxHeight - startButtonHeight - 20;
    startButton.setSize(sf::Vector2f(startButtonWidth, startButtonHeight));
    startButton.setPosition({startButtonX, startButtonY});

    menuButton.setSize(sf::Vector2f(title.getGlobalBounds().width / 3,
                                    title.getGlobalBounds().height / 2));
    menuButton.setPosition({50, 50 + title.getGlobalBounds().height / 2 -
                                    menuButton.getGlobalBounds().height / 2});

    for (int i = 0; i < static_cast<int>(textInputs.size()); i++) {
        textInputs[i].setPosition(
            sf::Vector2f(inputBoxX + 10, inputBoxY + 10 + i * 120));
        textInputs[i].setSize(sf::Vector2f(inputBoxWidth - 20, 120));
    }
}

void ConfigSimulation::draw() {
    window->clear(AppStyle::Colors::bgCyan);
    window->draw(titleBox);
    window->draw(title);
    window->draw(inputBox);
    startButton.draw(*window);
    menuButton.draw(*window);
    for (auto &textInput : textInputs) {
        textInput.draw(*window);
    }
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

            if (menuButton.getGlobalBounds().contains(mousePosition.x,
                                                      mousePosition.y)) {
                selectedScene = Scene::MENU;
            }

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

                system->simulate();

                simulationWindow.getLegend().clearItems();
                simulationWindow.getLegend().addItems(
                    {LegendItem<double>(
                         std::string("End X"),
                         system->getCollisions().back().getPos()[0], "m"),
                     LegendItem<double>(
                         std::string("End Y"),
                         system->getCollisions().back().getPos()[1], "m"),
                     LegendItem<double>(
                         "End Theta", system->getCollisions().back().getTheta(),
                         "rad")});

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
