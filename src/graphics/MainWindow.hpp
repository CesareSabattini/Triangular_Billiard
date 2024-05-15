#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../simulation/System.hpp"
#include "AnalysisWindow.hpp"
#include "ConfigSimulation.hpp"
#include "Menu.hpp"
#include "Scene.hpp"
#include "SimulationWindow.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class MainWindow {
  public:
    MainWindow();
    void run();
    Scene selectedScene;

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
    Menu menu;
    SimulationWindow simulationWindow;
    ConfigSimulation configSimulation;
    AnalysisWindow analysisWindow;

    void switchToConfig();
};

#endif