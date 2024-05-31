// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "../../simulation/system.hpp"

#include "../components/button/button.hpp"
#include "../components/textInput/textInput.hpp"
#include "../style/appStyle.hpp"
#include "../utils/scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics::scenes {

class Menu {
public:
  Menu(std::shared_ptr<sf::RenderWindow> window,
       std::shared_ptr<simulation::System<float>> system, Scene &selectedScene,
       const std::shared_ptr<sf::Font> font);
  void draw();
  void processEvents();

private:
  std::shared_ptr<sf::Font> font;
  std::shared_ptr<simulation::System<float>> system;
  std::shared_ptr<sf::RenderWindow> window;
  Scene &selectedScene;
  sf::Text title;
  sf::RectangleShape titleBox;

  graphics::components::Button configButton;

  graphics::components::Button analysisButton;

  sf::Texture backgroundTexture;
  sf::Sprite bg;

  void initializeComponents();
};

} // namespace graphics::scenes

#endif
