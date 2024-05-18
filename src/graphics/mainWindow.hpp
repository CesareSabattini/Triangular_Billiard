#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../simulation/system.hpp"
#include "analysisWindow.hpp"
#include "appStyle.hpp"
#include "configSimulation.hpp"
#include "menu.hpp"
#include "scene.hpp"
#include "simulationWindow.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class MainWindow {
  public:
    MainWindow();
    void run();
    Scene selectedScene;

  private:
    AppStyle::AppStyle appStyle;
    std::shared_ptr<System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Menu menu;
    ConfigSimulation configSimulation;
    SimulationWindow simulationWindow;
    AnalysisWindow analysisWindow;

    void switchToConfig();
};

#endif