#include "AnalysisWindow.hpp"

AnalysisWindow::AnalysisWindow(std::shared_ptr<sf::RenderWindow> p_window,
                               std::shared_ptr<System<double>> p_system,
                               Scene &p_selectedScene)
    : system(p_system), window(p_window), selectedScene(p_selectedScene),
      menuButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                 AppStyle::Colors::cream, AppStyle::Colors::cream.Blue,
                 AppStyle::Colors::cream.Black, AppStyle::Colors::bgCyan,
                 "Menu", 20),
      analyzeButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                    AppStyle::Colors::cream, AppStyle::Colors::cream.Blue,
                    AppStyle::Colors::cream.Black, AppStyle::Colors::bgCyan,
                    "Analyze", 30),
      resultsPanel({LegendItem<double>("Mean Y", 0.00, "m"),
                    LegendItem<double>("Std Y", 0.00, "m"),
                    LegendItem<double>("Mean Theta", 0.00, "rad"),
                    LegendItem<double>("Std Theta", 0.00, "rad")},
                   sf::Vector2f(20, 20), AppStyle::Colors::opaqueBlack,
                   sf::Color::White),
      textInputs({TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Pool length", "1000"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Start Radius", "200"),
                  TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "End radius", "100"),
                  TextInput(sf::Vector2f(100, 500), sf::Vector2f(200, 50), 24,
                            AppStyle::Colors::cream, AppStyle::Colors::bgCyan,
                            "Num Simulations", "100")}) {
    font.loadFromFile("../resources/theme_font.ttf");
    initializeComponents();
}

void AnalysisWindow::initializeComponents() {
    title.setFont(font);
    title.setString("Simulation Analysis");
    title.setCharacterSize(window->getSize().x / 20);
    title.setFillColor(AppStyle::Colors::bgCyan);
    title.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                          title.getGlobalBounds().width / 2.f,
                      50.f);

    titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50,
                                  title.getGlobalBounds().height + 50));
    titleBox.setFillColor(AppStyle::Colors::cream);
    titleBox.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                             titleBox.getGlobalBounds().width / 2,
                         title.getPosition().y);

    menuButton.setSize(sf::Vector2f(title.getGlobalBounds().width / 3,
                                    title.getGlobalBounds().height / 2));

    menuButton.setPosition({50, 50 + title.getGlobalBounds().height / 2 -
                                    menuButton.getGlobalBounds().height / 2});

    inputBox.setSize(
        sf::Vector2f(static_cast<float>(window->getSize().x) / 3.f,
                     static_cast<float>(window->getSize().y) / 2.f));
    inputBox.setFillColor(AppStyle::Colors::opaqueBlack);
    inputBox.setPosition(static_cast<float>(window->getSize().x) / 4.f -
                             inputBox.getGlobalBounds().width / 2,
                         static_cast<float>(window->getSize().y) / 5.f);

    float textInputWidth = inputBox.getGlobalBounds().width * 0.8f;
    float textInputHeight = inputBox.getGlobalBounds().height /
                            (static_cast<float>(textInputs.size()) + 3.f);
    for (std::array<TextInput, 4>::size_type i = 0; i < textInputs.size();
         i++) {
        textInputs[i].setSize(sf::Vector2f(textInputWidth, textInputHeight));
        textInputs[i].setPosition(sf::Vector2f(
            inputBox.getPosition().x + inputBox.getGlobalBounds().width / 2.f -
                textInputWidth / 2,
            inputBox.getPosition().y +
                static_cast<float>(i) * textInputHeight * 1.3f +
                textInputHeight / 2));
    }

    analyzeButton.setSize(sf::Vector2f(inputBox.getGlobalBounds().width / 2,
                                       inputBox.getGlobalBounds().height / 6));

    analyzeButton.setPosition({inputBox.getPosition().x +
                                   inputBox.getGlobalBounds().width / 2 -
                                   analyzeButton.getGlobalBounds().width / 2,
                               inputBox.getPosition().y + inputBox.getSize().y +
                                   analyzeButton.getGlobalBounds().height / 3});

    backgroundTexture.loadFromFile("../resources/pool_cover.jpg");
    bg.setTexture(backgroundTexture);

    resultsText.setFont(font);
    resultsText.setString("Results: ");
    resultsText.setCharacterSize(30);
    resultsText.setFillColor(AppStyle::Colors::bgCyan);

    resultsPanel.setSize(
        sf::Vector2f(static_cast<float>(window->getSize().x) / 3,
                     static_cast<float>(window->getSize().y) / 2));
    resultsPanel.setPosition(
        {static_cast<float>(window->getSize().x) * 3.0f / 4.0f -
             static_cast<float>(window->getSize().x) / 6.0f,
         static_cast<float>(window->getSize().y) / 5.0f});
}

void AnalysisWindow::draw() {
    window->clear(AppStyle::Colors::bgCyan);
    window->draw(titleBox);
    window->draw(title);
    menuButton.draw(*window);
    analyzeButton.draw(*window);
    window->draw(inputBox);
    window->draw(resultsText);
    for (auto &textInput : textInputs) {
        textInput.draw(*window);
    }
    window->draw(resultsPanel);
    window->display();
}

void AnalysisWindow::processEvents() {
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
                        static_cast<float>(mousePosition.x),
                        static_cast<float>(mousePosition.y))) {
                    textInput.setFocus(true);
                    anyInputFocused = true;
                } else {
                    textInput.setFocus(false);
                }
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

        if (menuButton.getGlobalBounds().contains(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y))) {
            selectedScene = Scene::MENU;
        }
        if (analyzeButton.getGlobalBounds().contains(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y))) {
            const int numSimulations = std::stoi(textInputs[3].getText());
            system->updateParams(0, 0, std::stod(textInputs[0].getText()),
                                 std::stod(textInputs[1].getText()),
                                 std::stod(textInputs[2].getText()));
            Analysis::Analyzer<double> analyzer(system, numSimulations);
            analyzer.generate();
            analyzer.simulate();
            analyzer.analyze();
            analyzer.printResults();
            resultsPanel.clearItems();
            sf::Vector2f currentPos = resultsPanel.getPosition();
            resultsPanel.addItems(
                {LegendItem<double>("Mean Y", analyzer.getResults().meanY, "m"),
                 LegendItem<double>("Std Y", analyzer.getResults().stdY, "m"),
                 LegendItem<double>("Mean Theta",
                                    analyzer.getResults().meanTheta, "rad"),
                 LegendItem<double>("Std Theta", analyzer.getResults().stdTheta,
                                    "rad")});
            resultsPanel.setPosition(currentPos);
        }
    }
}
