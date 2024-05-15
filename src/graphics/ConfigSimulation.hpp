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
    Scene &selectedScene;
    SimulationWindow &simulationWindow;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape titleBox;
    sf::RectangleShape inputBox;
    Button startButton;
    std::array<TextInput, 5> textInputs;
    Button menuButton;

    void initializeComponents();
};

#endif
