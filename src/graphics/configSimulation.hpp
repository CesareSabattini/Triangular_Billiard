#ifndef CONFIGSIMULATION_HPP
#define CONFIGSIMULATION_HPP
#include "../simulation/system.hpp"
#include "simulationWindow.hpp"

#include "appStyle.hpp"
#include "components/button/button.hpp"
#include "components/textInput/textInput.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class ConfigSimulation {
  public:
    ConfigSimulation(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<System<float>> system,
                     Scene &selectedScene, SimulationWindow &simulationWindow);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;
    SimulationWindow &simulationWindow;
    Button startButton;
    Button menuButton;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape titleBox;
    sf::RectangleShape inputBox;
    std::array<TextInput, 5> textInputs;

    void initializeComponents();
};

#endif
