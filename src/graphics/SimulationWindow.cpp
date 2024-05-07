
#include "SimulationWindow.hpp"

SimulationWindow::SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<System<double>> system)
    : window(window), system(system) {}

void SimulationWindow::run() {

    std::cout << "Collision Size: " << system->getCollisions().size() << "\n";

    sf::CircleShape ball(5);
    ball.setFillColor(sf::Color::Red);

    sf::VertexArray lines(sf::LinesStrip);
    sf::VertexArray poolWalls(sf::Lines);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::Blue);

        const auto &collisions = system->getCollisions();
        const auto &pool = system->getPool();

        const auto widthPortion = window->getSize().x / pool.getL();
        const auto heightPortion =
            window->getSize().y / (pool.getR1() + pool.getR2());

        if (!collisions.empty()) {
            lines.clear();
            for (auto &collision : collisions) {

                sf::Vector2f position(collision.getPos()[0] * widthPortion,
                                      collision.getPos()[1] * heightPortion);
                lines.append(sf::Vertex(position, sf::Color::White));

                ball.setPosition(position);
                window->draw(ball);
            }
        }
        poolWalls.clear();
        double scaleX = window->getSize().x / pool.getL();
        double scaleY = window->getSize().y / (pool.getR1() + pool.getR2());

        // Parete superiore
        poolWalls.append(
            sf::Vertex(sf::Vector2f(0, window->getSize().y / 2 +
                                           pool.getR1() * heightPortion),
                       sf::Color::White));
        poolWalls.append(sf::Vertex(
            sf::Vector2f(window->getSize().x, window->getSize().y / 2 +
                                                  pool.getR2() * heightPortion),
            sf::Color::White));

        // Parete inferiore
        poolWalls.append(
            sf::Vertex(sf::Vector2f(0, window->getSize().y / 2 -
                                           pool.getR1() * heightPortion),
                       sf::Color::White));
        poolWalls.append(sf::Vertex(
            sf::Vector2f(window->getSize().x, window->getSize().y / 2 -
                                                  pool.getR2() * heightPortion),
            sf::Color::White));

        window->draw(lines);
        window->draw(poolWalls);
        window->display();
    }
}
