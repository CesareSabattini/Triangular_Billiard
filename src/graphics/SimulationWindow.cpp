
#include "SimulationWindow.hpp"

SimulationWindow::SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                                   std::shared_ptr<System<double>> system)
    : window(window), system(system) {}

void SimulationWindow::run() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear(sf::Color::Blue);
        window->display();
    }
}
