#ifndef SIMULATION_WINDOW_HPP
#define SIMULATION_WINDOW_HPP

#include "../simulation/System.hpp"
#include "Scene.hpp"
#include "components/Legend.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class SimulationWindow {
  public:
    SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<System<double>> system,
                     Scene &selectedScene);
    void run();

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    sf::Font font;

    sf::RectangleShape menuButton;
    sf::Text menuButtonText;

    Legend<double> legend;

    Scene &selectedScene;
};

#endif