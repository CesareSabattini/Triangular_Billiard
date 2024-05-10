#include "MainWindow.hpp"

MainWindow::MainWindow()
    : window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]),
          "Triangular Pool Simulation")),
      system(std::make_shared<System<double>>()),
      menu(window, system, selectedScene),
      configSimulation(window, system, selectedScene),
      simulationWindow(window, system), selectedScene(Scene::MENU) {
    window->setPosition(sf::Vector2i(0, 0));
}

void MainWindow::run() {
    while (window->isOpen()) {

        window->clear();
        if (selectedScene == Scene::MENU) {
            menu.processEvents();
            menu.draw();
        }
        if (selectedScene == Scene::CONFIG) {
            switchToConfig();
        }
        if (selectedScene == Scene::SIMULATION) {
            system->simulate();
            switchToSimulation();
        }
        if (selectedScene == Scene::ANALYSIS) {
            analysisWindow.processEvents();
            analysisWindow.draw();
        }
    }
}

void MainWindow::switchToSimulation() { simulationWindow.run(); }

void MainWindow::switchToConfig() {
    configSimulation.processEvents();
    configSimulation.draw();
}