
#include "SimulationWindow.hpp"

SimulationWindow::SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<System<double>> system)
    : window(window), system(system) {}

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
        if (!collisions.empty()) {
            lines.clear();
            for (auto &collision : collisions) {

                sf::Vector2f position(collision.getPos()[0],
                                      collision.getPos()[1] + 500);
                lines.append(sf::Vertex(position, sf::Color::White));

                ball.setPosition(position);
                window->draw(ball);
            }
        }
        window->draw(lines);

        window->display();
    }
}
