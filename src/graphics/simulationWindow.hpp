#ifndef SIMULATION_WINDOW_HPP
#define SIMULATION_WINDOW_HPP

#include "../simulation/system.hpp"
#include "appStyle.hpp"
#include "components/button/button.hpp"
#include "components/legend/legend.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class SimulationWindow {
  public:
    SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<System<float>> system,
                     Scene &selectedScene,
                     const std::shared_ptr<sf::Font> font);

    void draw();
    void processEvents();

    Legend<float> &getLegend() { return legend; }

  private:
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;

    Button menuButton;

    Legend<float> legend;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    void initializeComponents();
};

#endif