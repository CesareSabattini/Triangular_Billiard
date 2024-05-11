
#include "SimulationWindow.hpp"

SimulationWindow::SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<System<double>> system)
    : window(window), system(system),
      legend(std::vector<LegendItem<double>>{},
             sf::Vector2f(window->getSize().x / 6, window->getSize().y / 4),
             sf::Color::White) {

    // Image by
    // https://www.freepik.com/free-vector/flat-design-poker-table-background_88532182.htm#query=pool%20table%20texture&position=3&from_view=keyword&track=ais&uuid=d397caa0-f20e-4ea8-a4cc-3ff86f785fbd

    if (!backgroundTexture.loadFromFile("../resources/pool_cover.jpg")) {
        throw std::runtime_error("Cannot load background texture");
    } else {
        bg.setTexture(backgroundTexture);
    }

    bg.setScale(window->getSize().x / bg.getLocalBounds().width,
                window->getSize().y / bg.getLocalBounds().height);

    bg.setPosition(0, 0);

    legend.addItem(
        LegendItem<double>(std::string("End X: "), 0, std::string("m")));
    legend.addItem(

        LegendItem<double>(std::string("Output Y: "), 0, std::string("m")));

    legend.addItem(LegendItem<double>(std::string("Output Theta: "), 0,
                                      std::string("rad")));

    legend.addItem(LegendItem<double>(std::string("Number of collisions"),
                                      (int)system->getCollisions().size(),
                                      std::string("")));
}

void SimulationWindow::run() {

    sf::CircleShape ball(5);
    ball.setFillColor(sf::Color::Red);

    sf::VertexArray lines(sf::LinesStrip);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::Blue);

        const auto &collisions = system->getCollisions();
        const auto &pool = system->getPool();

        if (!collisions.empty()) {
            lines.clear();
            for (auto &collision : collisions) {

                sf::Vector2f position(
                    (collision.getPos()[0] / pool.getL()) * window->getSize().x,

                    window->getSize().y / 2 -
                        (collision.getPos()[1] / pool.getR1()) *
                            window->getSize().y / 4);

                lines.append(sf::Vertex(position, sf::Color::White));

                ball.setPosition(position);
                window->draw(ball);
            }
        }
        double wallThickness = 10;
        sf::Color wallColor = sf::Color::Black;

        float angle = std::atan((((window->getSize().y / 4) * pool.getR2() /
                                  pool.getR1()) -
                                 window->getSize().y / 4) /
                                window->getSize().x) *
                      180 / M_PI;

        sf::RectangleShape inclinedUpperWall(
            sf::Vector2f(window->getSize().x, wallThickness));
        inclinedUpperWall.setPosition(0, window->getSize().y / 2 -
                                             window->getSize().y / 4 -
                                             wallThickness);
        inclinedUpperWall.setRotation(-angle);
        inclinedUpperWall.setFillColor(wallColor);

        sf::RectangleShape inclinedLowerWall(
            sf::Vector2f(window->getSize().x, wallThickness));
        inclinedLowerWall.setPosition(0, window->getSize().y / 2 +

                                             window->getSize().y / 4);
        inclinedLowerWall.setRotation(angle);
        inclinedLowerWall.setFillColor(wallColor);

        legend.setPosition(sf::Vector2f(
            window->getSize().x - window->getSize().x / 6 - 20, 20));

        window->draw(bg);
        window->draw(legend);
        window->draw(inclinedUpperWall);
        window->draw(inclinedLowerWall);

        window->draw(lines);
        window->display();
    }
}
