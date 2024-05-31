#include "analysisWindow.hpp"

graphics::scenes::AnalysisWindow::AnalysisWindow(
    std::shared_ptr<sf::RenderWindow> p_window,
    std::shared_ptr<simulation::System<float>> p_system, Scene &p_selectedScene,
    const std::shared_ptr<sf::Font> p_font)
    : font(p_font), system(p_system), window(p_window),
      selectedScene(p_selectedScene),
      menuButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                 appStyle::Colors::cream, appStyle::Colors::cream.Blue,
                 appStyle::Colors::cream.Black, appStyle::Colors::bgCyan,
                 "Menu", 20, p_font),
      analyzeButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                    appStyle::Colors::cream, appStyle::Colors::cream.Blue,
                    appStyle::Colors::cream.Black, appStyle::Colors::bgCyan,
                    "Analyze", 30, p_font),
      resultsPanel(
          {graphics::components::LegendItem<float>("Num exits", 0.00, "", 0),
           graphics::components::LegendItem<float>("Mean Y", 0.00, "m"),
           graphics::components::LegendItem<float>("Std Y", 0.00, "m"),
           graphics::components::LegendItem<float>("Mean Theta", 0.00, "rad"),
           graphics::components::LegendItem<float>("Std Theta", 0.00, "rad"),
           graphics::components::LegendItem<float>("Skewness Y", 0.00, ""),
           graphics::components::LegendItem<float>("Skewness Theta", 0.00, ""),
           graphics::components::LegendItem<float>("Kurtosis Y", 0.00, ""),
           graphics::components::LegendItem<float>("Kurtosis Theta", 0.00, "")},
          sf::Vector2f(20, 20), appStyle::Colors::opaqueBlack, p_font,
          sf::Color::White),
      textInputs({

          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Pool length", "1000"),
          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Start Radius", "200"),
          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "End radius", "100"),
          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Mean Y", "0"),
          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Std Y", "0.1"),
          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Mean Theta", "0"),
          graphics::components::TextInput(
              sf::Vector2f(100, 100), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Std Theta", "0.1"),
          graphics::components::TextInput(
              sf::Vector2f(100, 500), sf::Vector2f(200, 50), 24,
              appStyle::Colors::cream, p_font, appStyle::Colors::bgCyan,
              "Num Simulations", "100")}) {
  initializeComponents();
}

void graphics::scenes::AnalysisWindow::initializeComponents() {
  title.setFont(*font);
  title.setString("Simulation Analysis");
  title.setCharacterSize(window->getSize().x / 20);
  title.setFillColor(appStyle::Colors::bgCyan);
  title.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                        title.getGlobalBounds().width / 2.f,
                    50.f);

  titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50,
                                title.getGlobalBounds().height + 50));
  titleBox.setFillColor(appStyle::Colors::cream);
  titleBox.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                           titleBox.getGlobalBounds().width / 2,
                       title.getPosition().y);

  menuButton.setSize(sf::Vector2f(title.getGlobalBounds().width / 3,
                                  title.getGlobalBounds().height / 2));

  menuButton.setPosition({50, 50 + title.getGlobalBounds().height / 2 -
                                  menuButton.getGlobalBounds().height / 2});

  inputBox.setSize(sf::Vector2f(static_cast<float>(window->getSize().x) / 3.f,
                                static_cast<float>(window->getSize().y) / 2.f));
  inputBox.setFillColor(appStyle::Colors::opaqueBlack);
  inputBox.setPosition(static_cast<float>(window->getSize().x) / 4.f -
                           inputBox.getGlobalBounds().width / 2,
                       static_cast<float>(window->getSize().y) / 4.f);

  float textInputWidth = inputBox.getGlobalBounds().width * 0.4f;
  float textInputHeight = inputBox.getGlobalBounds().height / 6.f;
  for (std::array<graphics::components::TextInput, 8>::size_type i = 0; i < 5;
       i++) {
    textInputs[i].setSize(sf::Vector2f(textInputWidth, textInputHeight));
    textInputs[i].setPosition(sf::Vector2f(
        inputBox.getPosition().x + inputBox.getGlobalBounds().width / 4.f -
            textInputWidth / 2,
        inputBox.getPosition().y +
            static_cast<float>(i) * textInputHeight * 1.3f +
            textInputHeight / 2));
  }

  for (std::array<graphics::components::TextInput, 8>::size_type i = 0; i < 4;
       i++) {
    textInputs[i + 4].setSize(sf::Vector2f(textInputWidth, textInputHeight));
    textInputs[i + 4].setPosition(sf::Vector2f(
        inputBox.getPosition().x + inputBox.getGlobalBounds().width * 3 / 4.f -
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

  backgroundTexture.loadFromFile("../../resources/pool_cover.jpg");
  bg.setTexture(backgroundTexture);

  resultsText.setFont(*font);
  resultsText.setString("Results: ");
  resultsText.setCharacterSize(30);
  resultsText.setFillColor(appStyle::Colors::bgCyan);

  resultsPanel.setSize(
      sf::Vector2f(static_cast<float>(window->getSize().x) / 3,
                   static_cast<float>(window->getSize().y) / 2));
  resultsPanel.setPosition(
      {static_cast<float>(window->getSize().x) * 3.0f / 4.0f -
           static_cast<float>(window->getSize().x) / 6.0f,
       static_cast<float>(window->getSize().y) / 4.0f});
}

void graphics::scenes::AnalysisWindow::draw() {
  window->clear(appStyle::Colors::bgCyan);
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

void graphics::scenes::AnalysisWindow::processEvents() {
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
      system->updateParams(0, 0, std::stof(textInputs[0].getText()),
                           std::stof(textInputs[1].getText()),
                           std::stof(textInputs[2].getText()));

      Analysis::Parameters<float> params(std::stoi(textInputs[7].getText()),
                                         std::stof(textInputs[3].getText()),
                                         std::stof(textInputs[4].getText()),
                                         std::stof(textInputs[5].getText()),
                                         std::stof(textInputs[6].getText()));

      Analysis::Analyzer<float> analyzer(system, params);
      analyzer.generate();
      analyzer.simulate();
      analyzer.analyze();
      analyzer.printResults();
      resultsPanel.clearItems();
      sf::Vector2f currentPos = resultsPanel.getPosition();
      resultsPanel.addItems(
          {graphics::components::LegendItem<float>(
               "Num of exits",
               static_cast<float>(analyzer.getResults().outputSize), "", 0),
           graphics::components::LegendItem<float>(
               "Mean Y", analyzer.getResults().meanY, "m"),
           graphics::components::LegendItem<float>(
               "Std Y", analyzer.getResults().stdY, "m"),
           graphics::components::LegendItem<float>(
               "Mean Theta", analyzer.getResults().meanTheta, "rad"),
           graphics::components::LegendItem<float>(
               "Std Theta", analyzer.getResults().stdTheta, "rad"),
           graphics::components::LegendItem<float>(
               "Skewness Y", analyzer.getResults().skewnessY, ""),
           graphics::components::LegendItem<float>(
               "Skewness Theta", analyzer.getResults().skewnessTheta, ""),
           graphics::components::LegendItem<float>(
               "Kurtosis Y", analyzer.getResults().kurtosisY, ""),
           graphics::components::LegendItem<float>(
               "Kurtosis Theta", analyzer.getResults().kurtosisTheta, "")

          });
      resultsPanel.setPosition(currentPos);
    }
  }
}
