#include "MainWindow.hpp"

MainWindow::MainWindow()
    : window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]),
          "Triangular Pool Simulation")),
      system(std::make_shared<System<double>>()),
      menu(window, system, selectedScene), simulationWindow(window, system),
      selectedScene(Scene::MENU) {
    window->setPosition(sf::Vector2i(0, 0));
}

void MainWindow::run() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        if (selectedScene == Scene::MENU) {
            menu.processEvents();
            menu.draw();
        }
        if (selectedScene == Scene::SIMULATION) {
            switchToSimulation();
        }
    }
}

void MainWindow::switchToSimulation() { simulationWindow.run(); }