#include "../simulation/System.hpp"
#include "Menu.hpp"
#include "SimulationWindow.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class MainWindow {
  public:
    MainWindow();
    void run();

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
    Menu menu;
    SimulationWindow simulationWindow;

    void switchToSimulation();
};