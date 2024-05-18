
#include "simulationWindow.hpp"

SimulationWindow::SimulationWindow(std::shared_ptr<sf::RenderWindow> p_window,
                                   std::shared_ptr<System<float>> p_system,
                                   Scene &scene,
                                   std::shared_ptr<sf::Font> p_font)
    : font(p_font), system(p_system), window(p_window), selectedScene(scene),
      menuButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0),
                 AppStyle::Colors::opaqueBlack,
                 AppStyle::Colors::opaqueBlack.Blue,
                 AppStyle::Colors::opaqueBlack.Black, AppStyle::Colors::cream,
                 "Menu", 20, p_font),
      legend(std::vector<LegendItem<float>>{},
             sf::Vector2f(static_cast<float>(window->getSize().x) / 6.f,
                          static_cast<float>(window->getSize().y) / 4.f),
             AppStyle::Colors::opaqueBlack, p_font, sf::Color::White)

{

    if (!backgroundTexture.loadFromFile("../resources/pool_cover.jpg")) {
        throw std::runtime_error("Cannot load background texture");
    } else {
        bg.setTexture(backgroundTexture);
    }

    initializeComponents();
}

void SimulationWindow::initializeComponents() {
    // Image by
    // https://www.freepik.com/free-vector/flat-design-poker-table-background_88532182.htm#query=pool%20table%20texture&position=3&from_view=keyword&track=ais&uuid=d397caa0-f20e-4ea8-a4cc-3ff86f785fbd

    bg.setScale(
        static_cast<float>(window->getSize().x) / bg.getLocalBounds().width,
        static_cast<float>(window->getSize().y) / bg.getLocalBounds().height);

    bg.setPosition(0, 0);

    menuButton.setSize(
        sf::Vector2f(static_cast<float>(window->getSize().x) / 10.f, 60.f));
    menuButton.setPosition({20, 20});
}

void SimulationWindow::processEvents() {

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

            if (menuButton.getGlobalBounds().contains(
                    static_cast<float>(mousePosition.x),
                    static_cast<float>(mousePosition.y))) {
                selectedScene = Scene::MENU;
            }
        }
    }
}

void SimulationWindow::draw() {
    sf::CircleShape ball(5);
    ball.setFillColor(sf::Color::Red);

    sf::VertexArray lines(sf::LinesStrip);

    const auto &collisions = system->getCollisions();
    const auto &pool = system->getPool();

    float wallThickness = 10.f;
    sf::Color wallColor = sf::Color::Black;

    float majorBaseLength = pool.getR1() * 2.f;
    float length = pool.getL();
    float alpha = std::atan(
        (static_cast<float>(pool.getR1()) - static_cast<float>(pool.getR2())) /
        length);

    float fixedSide =
        static_cast<float>(window->getSize().y) - 6.f * wallThickness;

    float unity = 0.f;

    if (majorBaseLength > length) {
        unity = fixedSide / (majorBaseLength + 2 * wallThickness);
    } else {
        unity = fixedSide / (length + 2 * wallThickness);
    }

    sf::RectangleShape majorBase(
        sf::Vector2f(static_cast<float>(wallThickness),
                     static_cast<float>(majorBaseLength * unity)));

    sf::RectangleShape upperSide(sf::Vector2f(
        static_cast<float>(std::sqrt(std::pow(length, 2) +
                                     std::pow(pool.getR1() - pool.getR2(), 2)) *
                           unity),
        static_cast<float>(wallThickness)));

    sf::RectangleShape lowerSide(sf::Vector2f(
        static_cast<float>(std::sqrt(std::pow(length, 2) +
                                     std::pow(pool.getR1() - pool.getR2(), 2)) *
                           unity),
        static_cast<float>(wallThickness)));

    majorBase.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                              static_cast<float>(upperSide.getSize().x) / 2.f,
                          static_cast<float>(window->getSize().y) / 2.f -
                              static_cast<float>(majorBase.getSize().y) / 2.f -
                              2 * wallThickness);

    upperSide.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                              static_cast<float>(upperSide.getSize().x) / 2.f,
                          static_cast<float>(window->getSize().y) / 2.f -
                              static_cast<float>(majorBase.getSize().y) / 2.f -
                              2 * wallThickness);

    lowerSide.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                              static_cast<float>(upperSide.getSize().x) / 2.f,
                          static_cast<float>(window->getSize().y) / 2.f +
                              static_cast<float>(majorBase.getSize().y) / 2.f -
                              2 * wallThickness);

    upperSide.setRotation(alpha * 180.f / static_cast<float>(M_PI));
    lowerSide.setRotation(-alpha * 180.f / static_cast<float>(M_PI));

    upperSide.setFillColor(wallColor);
    lowerSide.setFillColor(wallColor);
    majorBase.setFillColor(wallColor);

    if (!collisions.empty()) {
        lines.clear();
        for (auto &collision : collisions) {

            sf::Vector2f position(
                majorBase.getPosition().x + wallThickness +
                    static_cast<float>(collision.getPos()[0]) * unity,
                majorBase.getPosition().y + majorBase.getSize().y / 2 +
                    static_cast<float>(collision.getPos()[1]) * unity);

            lines.append(sf::Vertex(position, sf::Color::White));

            ball.setPosition(position);
            window->draw(ball);
        }
    }

    legend.setPosition(
        sf::Vector2f(static_cast<float>(window->getSize().x) -
                         static_cast<float>(window->getSize().x) / 6.f - 20.f,
                     20.f));

    window->draw(bg);
    window->draw(legend);
    window->draw(majorBase);
    window->draw(upperSide);
    window->draw(lowerSide);
    menuButton.draw(*window);

    window->draw(lines);
    window->display();
}
