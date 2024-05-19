#include "configSimulation.hpp"

ConfigSimulation::ConfigSimulation(std::shared_ptr<sf::RenderWindow> p_window,
                                   std::shared_ptr<System<float>> p_system,
                                   Scene &p_selectedScene,
                                   SimulationWindow &p_simulationWindow,
                                   const std::shared_ptr<sf::Font> p_font)
    : font(p_font), system(p_system), window(p_window),
      selectedScene(p_selectedScene), simulationWindow(p_simulationWindow),
      startButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f),
                  AppStyle::Colors::darkGreen, AppStyle::Colors::darkGreen.Blue,
                  AppStyle::Colors::darkGreen.Black, AppStyle::Colors::cream,
                  "Start Simulation", 20, p_font),
      menuButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f),
                 AppStyle::Colors::cream, AppStyle::Colors::cream.Blue,
                 AppStyle::Colors::cream.Black, AppStyle::Colors::bgCyan,
                 "Menu", 20, p_font),

      textInputs(
          {TextInput(sf::Vector2f(100.f, 100.f), sf::Vector2f(200.f, 50.f), 24,
                     AppStyle::Colors::cream, p_font, AppStyle::Colors::bgCyan,
                     "Ball start Angle (radians)", "1"),
           TextInput(sf::Vector2f(100.f, 100.f), sf::Vector2f(200.f, 50.f), 24,
                     AppStyle::Colors::cream, p_font, AppStyle::Colors::bgCyan,
                     "Ball start y", "0"),
           TextInput(sf::Vector2f(100.f, 100.f), sf::Vector2f(200.f, 50.f), 24,
                     AppStyle::Colors::cream, p_font, AppStyle::Colors::bgCyan,
                     "Pool length", "1000"),
           TextInput(sf::Vector2f(100.f, 100.f), sf::Vector2f(200.f, 50.f), 24,
                     AppStyle::Colors::cream, p_font, AppStyle::Colors::bgCyan,
                     "Start Radius", "200"),
           TextInput(sf::Vector2f(100.f, 100.f), sf::Vector2f(200.f, 50.f), 24,
                     AppStyle::Colors::cream, p_font, AppStyle::Colors::bgCyan,
                     "End radius", "100")}) {

    initializeComponents();
}
void ConfigSimulation::initializeComponents() {
    title.setFont(*font);
    title.setString("Configure Simulation");
    title.setCharacterSize(window->getSize().x / 20);
    title.setFillColor(AppStyle::Colors::bgCyan);
    title.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                          title.getGlobalBounds().width / 2.f,
                      50.f);

    titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50.f,
                                  title.getGlobalBounds().height + 50.f));
    titleBox.setFillColor(AppStyle::Colors::cream);
    titleBox.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                             titleBox.getGlobalBounds().width / 2.f,
                         title.getPosition().y);

    float inputBoxWidth = static_cast<float>(window->getSize().x) / 3.f;
    float inputBoxHeight = static_cast<float>(window->getSize().y) / 1.5f;
    float inputBoxX =
        static_cast<float>(window->getSize().x) / 2.f - inputBoxWidth / 2;
    float inputBoxY = static_cast<float>(window->getSize().y) / 5.f;

    inputBox.setSize(sf::Vector2f(inputBoxWidth, inputBoxHeight));
    inputBox.setFillColor(AppStyle::Colors::opaqueBlack);
    inputBox.setPosition(inputBoxX, inputBoxY);

    float startButtonWidth = inputBoxWidth / 2.f;
    float startButtonHeight = inputBoxHeight / 10.f;
    float startButtonX =
        static_cast<float>(window->getSize().x) / 2.f - startButtonWidth / 2.f;
    float startButtonY = inputBoxY + inputBoxHeight - startButtonHeight - 20.f;
    startButton.setSize(sf::Vector2f(startButtonWidth, startButtonHeight));
    startButton.setPosition({startButtonX, startButtonY});

    menuButton.setSize(sf::Vector2f(title.getGlobalBounds().width / 3.f,
                                    title.getGlobalBounds().height / 2.f));
    menuButton.setPosition(
        {50.f, 50.f + title.getGlobalBounds().height / 2.f -
                   menuButton.getGlobalBounds().height / 2.f});

    for (std::array<TextInput, 5>::size_type i = 0; i < textInputs.size();
         i++) {
        textInputs[i].setPosition(
            sf::Vector2f(inputBoxX + 10.f,
                         inputBoxY + 10.f + static_cast<float>(i) * 120.f));
        textInputs[i].setSize(sf::Vector2f(
            static_cast<float>(inputBoxWidth - static_cast<float>(20)), 120.f));
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

            if (menuButton.getGlobalBounds().contains(
                    static_cast<float>(mousePosition.x),
                    static_cast<float>(mousePosition.y))) {
                selectedScene = Scene::MENU;
            }

            bool anyInputFocused = false;
            for (auto &textInput : textInputs) {
                if (textInput.inputBox.getGlobalBounds().contains(
                        static_cast<float>(mousePosition.x),
                        static_cast<float>(mousePosition.y))) {
                    textInput.setFocus(true);
                    anyInputFocused = true;
                } else {
                    textInput.setFocus(false);
                }
            }

            if (startButton.getGlobalBounds().contains(
                    static_cast<float>(mousePosition.x),
                    static_cast<float>(mousePosition.y))) {
                system->updateParams(std::stof(textInputs[0].getText()),
                                     std::stof(textInputs[1].getText()),
                                     std::stof(textInputs[2].getText()),
                                     std::stof(textInputs[3].getText()),
                                     std::stof(textInputs[4].getText()));

                system->simulate();

                simulationWindow.getLegend().clearItems();
                simulationWindow.getLegend().addItems(
                    {LegendItem<float>(
                         std::string("End X"),
                         system->getCollisions().back().getPos()[0], "m"),
                     LegendItem<float>(
                         std::string("End Y"),
                         system->getCollisions().back().getPos()[1], "m"),
                     LegendItem<float>(
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
