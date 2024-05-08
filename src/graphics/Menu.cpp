#include "Menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> window,
           std::shared_ptr<System<double>> system, Scene &p_selectedScene)
    : window(window), system(system), selectedScene(p_selectedScene) {

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    initializeComponents();

    if (!backgroundTexture.loadFromFile("../resources/pool.jpg")) {
        throw std::runtime_error("Cannot load background texture");
    } else {
        bg.setTexture(backgroundTexture);
    }

    bg.setScale(window->getSize().x / bg.getLocalBounds().width,
                window->getSize().y / bg.getLocalBounds().height);

    bg.setPosition(0, 0);
}
void Menu::initializeComponents() {
    title.setFont(font);
    title.setString("Triangular Pool Simulation");
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

    double buttonWidth = window->getSize().x / 4;
    double buttonHeight = window->getSize().y / 10;

    double configButtonX = window->getSize().x / 4 - buttonWidth / 2;
    double configButtonY = window->getSize().y / 2 - buttonHeight / 2;
    configButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    configButton.setFillColor(sf::Color::Green);
    configButton.setPosition(configButtonX, configButtonY);

    configButtonText.setFont(font);
    configButtonText.setString("Simulation");
    configButtonText.setCharacterSize(20);
    configButtonText.setFillColor(sf::Color::Black);
    configButtonText.setPosition(
        configButtonX + buttonWidth / 2 -
            configButtonText.getGlobalBounds().width / 2,
        configButtonY + buttonHeight / 2 -
            configButtonText.getGlobalBounds().height / 2);

    double gaussButtonX = 3 * window->getSize().x / 4 - buttonWidth / 2;
    double gaussButtonY = window->getSize().y / 2 - buttonHeight / 2;
    gaussButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    gaussButton.setFillColor(sf::Color::Green);
    gaussButton.setPosition(gaussButtonX, gaussButtonY);

    gaussButtonText.setFont(font);
    gaussButtonText.setString("Gaussian Distribution");
    gaussButtonText.setCharacterSize(20);
    gaussButtonText.setFillColor(sf::Color::Black);
    gaussButtonText.setPosition(gaussButtonX + buttonWidth / 2 -
                                    gaussButtonText.getGlobalBounds().width / 2,
                                gaussButtonY + buttonHeight / 2 -
                                    gaussButtonText.getGlobalBounds().height /
                                        2);
}

void Menu::draw() {
    window->draw(bg);
    window->draw(titleBox);
    window->draw(title);
    window->draw(configButton);
    window->draw(configButtonText);
    window->draw(gaussButton);
    window->draw(gaussButtonText);

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
        }
    }
}
