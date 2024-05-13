#include "Menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window,
           std::shared_ptr<System<double>> system, Scene &p_selectedScene)
    : window(window), system(system), selectedScene(p_selectedScene) {

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
    title.setFillColor(sf::Color(2, 138, 160));
    title.setPosition(
        window->getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

    titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50,
                                  title.getGlobalBounds().height + 50));
    titleBox.setFillColor(sf::Color(246, 250, 222));
    titleBox.setPosition(window->getSize().x / 2 -
                             titleBox.getGlobalBounds().width / 2,
                         title.getPosition().y);

    double buttonWidth = window->getSize().x / 4;
    double buttonHeight = window->getSize().y / 10;

    double configButtonX = window->getSize().x / 4 - buttonWidth / 2;
    double configButtonY = window->getSize().y / 2 - buttonHeight / 2;
    configButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    configButton.setFillColor(sf::Color(246, 250, 222));
    configButton.setPosition(configButtonX, configButtonY);

    configButtonText.setFont(font);
    configButtonText.setString("Simulation");
    configButtonText.setCharacterSize(30);
    configButtonText.setFillColor(sf::Color(2, 138, 160));
    configButtonText.setPosition(
        configButtonX + buttonWidth / 2 -
            configButtonText.getGlobalBounds().width / 2,
        configButtonY + buttonHeight / 2 -
            configButtonText.getGlobalBounds().height / 2);

    double analysisButtonX = 3 * window->getSize().x / 4 - buttonWidth / 2;
    double analysisButtonY = window->getSize().y / 2 - buttonHeight / 2;
    analysisButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    analysisButton.setFillColor(sf::Color(246, 250, 222));
    analysisButton.setPosition(analysisButtonX, analysisButtonY);

    analysisButtonText.setFont(font);
    analysisButtonText.setString("Data Analysis");
    analysisButtonText.setCharacterSize(30);
    analysisButtonText.setFillColor(sf::Color(2, 138, 160));
    analysisButtonText.setPosition(
        analysisButtonX + buttonWidth / 2 -
            analysisButtonText.getGlobalBounds().width / 2,
        analysisButtonY + buttonHeight / 2 -
            analysisButtonText.getGlobalBounds().height / 2);
}

void Menu::draw() {
    window->clear(sf::Color(2, 138, 160));
    window->draw(bg);
    window->draw(titleBox);
    window->draw(title);
    window->draw(configButton);
    window->draw(configButtonText);
    window->draw(analysisButton);
    window->draw(analysisButtonText);

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
