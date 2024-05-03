#include "../simulation/System.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class SimulationWindow {
  public:
    SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<System<double>> system);
    void run();

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
};
