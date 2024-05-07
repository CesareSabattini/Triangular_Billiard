// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "../simulation/System.hpp"

#include "Scene.hpp"
#include "components/TextInput.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Menu {
  public:
    Menu(std::shared_ptr<sf::RenderWindow> window,
         std::shared_ptr<System<double>> system, Scene &selectedScene);
    void draw();
    void processEvents();

  private:
    Scene &selectedScene;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape inputBox;
    sf::RectangleShape startButton;
    sf::Text startButtonText;

    std::array<TextInput, 5> textInputs;

    void initializeComponents();
};

#endif
