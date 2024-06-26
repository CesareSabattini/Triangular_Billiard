#ifndef SIMULATION_WINDOW_HPP
#define SIMULATION_WINDOW_HPP

#include "../../simulation/system.hpp"
#include "../components/button/button.hpp"
#include "../components/legend/legend.hpp"
#include "../style/appStyle.hpp"
#include "../utils/scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics::scenes {
class SimulationWindow {
public:
  SimulationWindow(std::shared_ptr<sf::RenderWindow> window,
                   std::shared_ptr<simulation::System<float>> system,
                   Scene &selectedScene, const std::shared_ptr<sf::Font> font);

  void draw();
  void processEvents();

  graphics::components::Legend<float> &getLegend() { return legend; }

private:
  std::shared_ptr<sf::Font> font;
  std::shared_ptr<simulation::System<float>> system;
  std::shared_ptr<sf::RenderWindow> window;
  Scene &selectedScene;

  graphics::components::Button menuButton;

  graphics::components::Legend<float> legend;

  sf::Texture backgroundTexture;
  sf::Sprite bg;

  void initializeComponents();
};
} // namespace graphics::scenes

#endif