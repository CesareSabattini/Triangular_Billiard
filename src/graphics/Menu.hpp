// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "../simulation/System.hpp"

#include "AppStyle.hpp"
#include "Scene.hpp"
#include "components/button/Button.hpp"
#include "components/textInput/TextInput.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Menu {
  public:
    Menu(std::shared_ptr<sf::RenderWindow> window,
         std::shared_ptr<System<double>> system, Scene &selectedScene);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<System<double>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape titleBox;

    Button configButton;

    Button analysisButton;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    void initializeComponents();
};

#endif
