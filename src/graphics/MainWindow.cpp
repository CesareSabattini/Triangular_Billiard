#include "MainWindow.hpp"

MainWindow::MainWindow()
    : window(std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600),
                                                "Triangular Pool Simulation")),
      system(std::make_shared<System<double>>()), menu(window, system),
      simulationWindow(window, system) {}

void MainWindow::run() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        menu.draw();
        window->display();
    }
}

void MainWindow::switchToSimulation() { simulationWindow.run(); }