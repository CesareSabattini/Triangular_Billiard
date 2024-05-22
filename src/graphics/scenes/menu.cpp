#include "menu.hpp"

graphics::scenes::Menu::Menu(
    std::shared_ptr<sf::RenderWindow> p_window,
    std::shared_ptr<simulation::System<float>> p_system, Scene &p_selectedScene,
    const std::shared_ptr<sf::Font> p_font)
    : font(p_font), system(p_system), window(p_window),
      selectedScene(p_selectedScene),
      configButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                   appStyle::Colors::cream, appStyle::Colors::cream.Blue,
                   appStyle::Colors::cream.Black, appStyle::Colors::bgCyan,
                   "Simulation", 30, p_font),
      analysisButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                     appStyle::Colors::cream, appStyle::Colors::cream.Blue,
                     appStyle::Colors::cream.Black, appStyle::Colors::bgCyan,
                     "Data Analysis", 30, p_font) {

    initializeComponents();

    if (!backgroundTexture.loadFromFile("../resources/pool.jpeg")) {
        throw std::runtime_error("Cannot load background texture");
    } else {
        bg.setTexture(backgroundTexture);
    }

    bg.setScale(static_cast<float>(window->getSize().x) /
                    (2 * bg.getLocalBounds().width),
                static_cast<float>(window->getSize().y) /
                    bg.getLocalBounds().height);

    bg.setPosition(static_cast<float>(window->getSize().x) / 2.0f -
                       static_cast<float>(bg.getGlobalBounds().width) / 2.f,
                   static_cast<float>(window->getSize().y) / 2.0f -
                       bg.getGlobalBounds().height / 2.f);
}
void graphics::scenes::Menu::initializeComponents() {
    title.setFont(*font);
    title.setString("Triangular Pool Simulation");
    title.setCharacterSize(static_cast<unsigned int>(
        static_cast<float>(window->getSize().x) / 20.f));
    title.setFillColor(appStyle::Colors::bgCyan);
    title.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                          title.getGlobalBounds().width / 2.f,
                      50.f);

    titleBox.setSize(sf::Vector2f(title.getGlobalBounds().width + 50,
                                  title.getGlobalBounds().height + 50));
    titleBox.setFillColor(appStyle::Colors::cream);
    titleBox.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                             titleBox.getGlobalBounds().width / 2.f,
                         title.getPosition().y);

    float buttonWidth = static_cast<float>(window->getSize().x) / 4.f;
    float buttonHeight = static_cast<float>(window->getSize().y) / 10.f;

    float configButtonX =
        static_cast<float>(window->getSize().x) / 4.f - buttonWidth / 2.f;
    float configButtonY =
        static_cast<float>(window->getSize().y) / 2.f - buttonHeight / 2.f;
    configButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    configButton.setPosition({configButtonX, configButtonY});

    float analysisButtonX =
        3.f * static_cast<float>(window->getSize().x) / 4.f -
        static_cast<float>(buttonWidth) / 2.f;
    float analysisButtonY =
        static_cast<float>(window->getSize().y) / 2.f - buttonHeight / 2.f;
    analysisButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));

    analysisButton.setPosition({analysisButtonX, analysisButtonY});
}

void graphics::scenes::Menu::draw() {
    window->clear(appStyle::Colors::bgCyan);
    window->draw(bg);
    window->draw(titleBox);
    window->draw(title);
    configButton.draw(*window);
    analysisButton.draw(*window);

    window->display();
}

void graphics::scenes::Menu::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

            if (configButton.getGlobalBounds().contains(
                    static_cast<float>(mousePosition.x),
                    static_cast<float>(mousePosition.y))) {

                selectedScene = Scene::CONFIG;
            }
            if (analysisButton.getGlobalBounds().contains(
                    static_cast<float>(mousePosition.x),
                    static_cast<float>(mousePosition.y))) {
                selectedScene = Scene::ANALYSIS;
            }
        }
    }
}
