#ifndef CONFIGSIMULATION_HPP
#define CONFIGSIMULATION_HPP
#include "../../simulation/system.hpp"
#include "simulationWindow.hpp"

#include "../components/button/button.hpp"
#include "../components/errorPopup/errorPopup.hpp"
#include "../components/textInput/textInput.hpp"
#include "../style/appStyle.hpp"
#include "../utils/scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics::scenes {

class ConfigSimulation {
public:
  ConfigSimulation(std::shared_ptr<sf::RenderWindow> window,
                   std::shared_ptr<simulation::System<float>> system,
                   Scene &selectedScene, SimulationWindow &simulationWindow,
                   const std::shared_ptr<sf::Font> font);
  void draw();
  void processEvents();

private:
  std::shared_ptr<sf::Font> font;
  std::shared_ptr<simulation::System<float>> system;
  std::shared_ptr<sf::RenderWindow> window;
  Scene &selectedScene;
  SimulationWindow &simulationWindow;
  graphics::components::Button startButton;
  graphics::components::Button menuButton;
  sf::Text title;
  sf::RectangleShape titleBox;
  sf::RectangleShape inputBox;
  std::array<graphics::components::TextInput, 5> textInputs;

  void initializeComponents();
};

} // namespace graphics::scenes

#endif
