#include "mainWindow.hpp"

MainWindow::MainWindow()
    : selectedScene(Scene::MENU), system(std::make_shared<System<float>>()),
      window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]),
          "Triangular Pool Simulation")),

      menu(window, system, selectedScene),
      configSimulation(window, system, selectedScene, simulationWindow),
      simulationWindow(window, system, selectedScene),
      analysisWindow(window, system, selectedScene) {
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

            simulationWindow.processEvents();
            simulationWindow.draw();
        }
        if (selectedScene == Scene::ANALYSIS) {
            analysisWindow.processEvents();
            analysisWindow.draw();
        }
    }
}

void MainWindow::switchToConfig() {
    configSimulation.processEvents();
    configSimulation.draw();
}