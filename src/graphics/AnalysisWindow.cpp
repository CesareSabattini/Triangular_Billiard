#include "AnalysisWindow.hpp"

AnalysisWindow::AnalysisWindow(std::shared_ptr<sf::RenderWindow> window,
                               std::shared_ptr<System<double>> system,
                               Scene &selectedScene)
    : window(window), system(system), selectedScene(selectedScene),
      textInputs(
          {TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                     sf::Color::Red, sf::Color::Black, "Pool length", "1000"),
           TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                     sf::Color::Red, sf::Color::Black, "Start Radius", "200"),
           TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                     sf::Color::Red, sf::Color::Black, "End radius", "100"),
           TextInput(sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
                     sf::Color::Red, sf::Color::Black, "Num Simulations",
                     "100")}) {
    font.loadFromFile("resources/arial.ttf");
    initializeComponents();
}

void AnalysisWindow::initializeComponents() {
    title.setFont(font);
    title.setString("Analysis");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(50, 50);

    titleBox.setSize(sf::Vector2f(500, 100));
    titleBox.setFillColor(sf::Color(0, 0, 0, 150));
    titleBox.setPosition(40, 40);

    menuButton.setSize(sf::Vector2f(200, 50));
    menuButton.setFillColor(sf::Color(0, 0, 0, 150));
    menuButton.setPosition(50, 500);

    menuButtonText.setFont(font);
    menuButtonText.setString("Menu");
    menuButtonText.setCharacterSize(30);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(70, 500);

    analyzeButton.setSize(sf::Vector2f(200, 50));
    analyzeButton.setFillColor(sf::Color(0, 0, 0, 150));
    analyzeButton.setPosition(550, 500);

    analyzeButtonText.setFont(font);
    analyzeButtonText.setString("Analyze");
    analyzeButtonText.setCharacterSize(30);
    analyzeButtonText.setFillColor(sf::Color::White);
    analyzeButtonText.setPosition(570, 500);

    backgroundTexture.loadFromFile("resources/background.jpg");
    bg.setTexture(backgroundTexture);

    inputBox.setSize(sf::Vector2f(500, 50));
    inputBox.setFillColor(sf::Color(0, 0, 0, 150));
    inputBox.setPosition(50, 200);
    for (int i = 0; i < textInputs.size(); i++) {
        textInputs[i].setPosition(
            sf::Vector2f(inputBox.getPosition().x + 10,
                         inputBox.getPosition().y + 10 + i * 120));
        textInputs[i].setSize(
            sf::Vector2f(inputBox.getGlobalBounds().width - 20, 120));
    }

    resultsBox.setSize(sf::Vector2f(500, 200));
    resultsBox.setFillColor(sf::Color(0, 0, 0, 150));
    resultsBox.setPosition(
        window->getSize().x - resultsBox.getGlobalBounds().width - 50, 200);

    resultsText.setFont(font);
    resultsText.setString("Results: ");
    resultsText.setCharacterSize(30);
    resultsText.setFillColor(sf::Color::White);
    resultsText.setPosition(
        window->getSize().x - resultsBox.getGlobalBounds().width - 50, 200);
}

void AnalysisWindow::draw() {
    window->draw(bg);
    window->draw(titleBox);
    window->draw(title);
    window->draw(menuButton);
    window->draw(menuButtonText);
    window->draw(analyzeButton);
    window->draw(analyzeButtonText);
    window->draw(inputBox);
    for (auto &textInput : textInputs) {
        textInput.draw(*window);
    }
    window->draw(resultsBox);
    window->draw(resultsText);
}

void AnalysisWindow::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

                bool anyInputFocused = false;

                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition =
                        sf::Mouse::getPosition(*window);

                    for (auto &textInput : textInputs) {
                        if (textInput.inputBox.getGlobalBounds().contains(
                                mousePosition.x, mousePosition.y)) {
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
                    if (textInput.isFocused &&
                        event.type == sf::Event::TextEntered) {
                        textInput.handleEvent(event);
                    }
                }

                if (menuButton.getGlobalBounds().contains(
                        event.mouseButton.x, event.mouseButton.y)) {
                    selectedScene = Scene::MENU;
                }
                if (analyzeButton.getGlobalBounds().contains(
                        event.mouseButton.x, event.mouseButton.y)) {
                    const int numSimulations =
                        std::stoi(textInputs[3].getText());
                    // terminare la configurazione per visualizzazione dei
                    // risultati
                    Analysis<double> analyzer(system, numSimulations);
                    analyzer.analyze();
                    results = analyzer.getResults();
                }
            }
        }
    }
}
