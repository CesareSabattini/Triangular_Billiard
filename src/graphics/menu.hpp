// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "../simulation/system.hpp"

#include "appStyle.hpp"
#include "components/button/button.hpp"
#include "components/textInput/textInput.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Menu {
  public:
    Menu(std::shared_ptr<sf::RenderWindow> window,
         std::shared_ptr<System<float>> system, Scene &selectedScene,
         std::shared_ptr<sf::Font> font);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;
    sf::Text title;
    sf::RectangleShape titleBox;

    Button configButton;

    Button analysisButton;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    void initializeComponents();
};

#endif
