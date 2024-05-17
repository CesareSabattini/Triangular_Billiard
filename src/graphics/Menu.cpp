#include "Menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window,
           std::shared_ptr<System<double>> system, Scene &p_selectedScene)
    : system(system), window(window), selectedScene(p_selectedScene),
      configButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                   AppStyle::Colors::cream, AppStyle::Colors::cream.Blue,
                   AppStyle::Colors::cream.Black, AppStyle::Colors::bgCyan,
                   font, "Simulation", 30),
      analysisButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                     AppStyle::Colors::cream, AppStyle::Colors::cream.Blue,
                     AppStyle::Colors::cream.Black, AppStyle::Colors::bgCyan,
                     font, "Data Analysis", 30) {

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeComponents();

    if (!backgroundTexture.loadFromFile("../resources/pool.jpeg")) {
        throw std::runtime_error("Cannot load background texture");
    } else {
        bg.setTexture(backgroundTexture);
    }

    bg.setScale(window->getSize().x / (2 * bg.getLocalBounds().width),
                window->getSize().y / bg.getLocalBounds().height);

    bg.setPosition(window->getSize().x / 2 - bg.getGlobalBounds().width / 2,
                   window->getSize().y / 2 - bg.getGlobalBounds().height / 2);
}
void Menu::initializeComponents() {
    title.setFont(font);
    title.setString("Triangular Pool Simulation");
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

    float buttonWidth = window->getSize().x / 4;
    float buttonHeight = window->getSize().y / 10;

    float configButtonX = window->getSize().x / 4 - buttonWidth / 2;
    float configButtonY = window->getSize().y / 2 - buttonHeight / 2;
    configButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    configButton.setPosition({configButtonX, configButtonY});

    float analysisButtonX = 3 * window->getSize().x / 4 - buttonWidth / 2;
    float analysisButtonY = window->getSize().y / 2 - buttonHeight / 2;
    analysisButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));

    analysisButton.setPosition({analysisButtonX, analysisButtonY});
}

void Menu::draw() {
    window->clear(AppStyle::Colors::bgCyan);
    window->draw(bg);
    window->draw(titleBox);
    window->draw(title);
    configButton.draw(*window);
    analysisButton.draw(*window);

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

            if (configButton.getGlobalBounds().contains(mousePosition.x,
                                                        mousePosition.y)) {

                selectedScene = Scene::CONFIG;
            }
            if (analysisButton.getGlobalBounds().contains(mousePosition.x,
                                                          mousePosition.y)) {
                selectedScene = Scene::ANALYSIS;
            }
        }
    }
}
