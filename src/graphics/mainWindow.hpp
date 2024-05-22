#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../simulation/system.hpp"
#include "scenes/analysisWindow.hpp"
#include "scenes/configSimulation.hpp"
#include "scenes/menu.hpp"
#include "scenes/simulationWindow.hpp"
#include "style/appStyle.hpp"
#include "utils/scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics {

class MainWindow {
  public:
    MainWindow();
    void run();
    Scene selectedScene;

  private:
    appStyle::AppStyle appStyle;
    std::shared_ptr<simulation::System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    graphics::scenes::Menu menu;
    graphics::scenes::ConfigSimulation configSimulation;
    graphics::scenes::SimulationWindow simulationWindow;
    graphics::scenes::AnalysisWindow analysisWindow;

    void switchToConfig();
};
} // namespace graphics

#endif