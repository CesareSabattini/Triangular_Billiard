#ifndef SIMULATION_WINDOW_HPP
#define SIMULATION_WINDOW_HPP

#include "../simulation/System.hpp"
#include "AppStyle.hpp"
#include "Scene.hpp"
#include "components/button/Button.hpp"
#include "components/legend/Legend.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class SimulationWindow {
  public:
    SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<System<double>> system,
                     Scene &selectedScene);

    void draw();
    void processEvents();

    Legend<double> &getLegend() { return legend; }

  private:
    std::shared_ptr<System<double>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;

    Button menuButton;

    Legend<double> legend;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    sf::Font font;

    void initializeComponents();
};

#endif