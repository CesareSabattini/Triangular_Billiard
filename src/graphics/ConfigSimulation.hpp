#ifndef CONFIGSIMULATION_HPP
#define CONFIGSIMULATION_HPP
#include "../simulation/System.hpp"
#include "SimulationWindow.hpp"

#include "AppStyle.hpp"
#include "Scene.hpp"
#include "components/button/Button.hpp"
#include "components/textInput/TextInput.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class ConfigSimulation {
  public:
    ConfigSimulation(std::shared_ptr<sf::RenderWindow> window,
                     std::shared_ptr<System<double>> system,
                     Scene &selectedScene, SimulationWindow &simulationWindow);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<System<double>> system;
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
