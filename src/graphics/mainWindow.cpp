#include "mainWindow.hpp"

graphics::MainWindow::MainWindow()
    : selectedScene(Scene::MENU),
      system(std::make_shared<simulation::System<float>>()),
      window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]),
          "Triangular Pool Simulation")),

      menu(window, system, selectedScene, (appStyle.getFont())),
      configSimulation(window, system, selectedScene, simulationWindow,
                       appStyle.getFont()),
      simulationWindow(window, system, selectedScene, appStyle.getFont()),
      analysisWindow(window, system, selectedScene, appStyle.getFont()) {
    window->setPosition(sf::Vector2i(0, 0));
}

void graphics::MainWindow::run() {
    while (window->isOpen()) {
        window->clear();
        try {
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
        } catch (std::invalid_argument &e) {
            graphics::components::ErrorPopup errorPopup(
                window, appStyle.getFont(), e.what(), selectedScene);
            selectedScene = Scene::ERROR;
            while (selectedScene == Scene::ERROR) {
                errorPopup.processEvents();
                window->clear();
                errorPopup.draw();
                window->display();
            }
        }
    }
}

void graphics::MainWindow::switchToConfig() {
    configSimulation.processEvents();
    configSimulation.draw();
}