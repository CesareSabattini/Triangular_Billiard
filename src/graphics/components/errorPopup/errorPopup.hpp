#ifndef ERRORPOPUP_HPP
#define ERRORPOPUP_HPP

#include "../../style/appStyle.hpp"
#include "../../utils/scene.hpp"
#include "../button/button.hpp"

#include <SFML/Graphics.hpp>

namespace graphics::components {

class ErrorPopup {
  public:
    ErrorPopup(std::shared_ptr<sf::RenderWindow> window,
               const std::shared_ptr<sf::Font> font, const std::string &message,
               Scene &selectedScene);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<sf::RenderWindow> window;
    Button okButton;
    sf::Text message;
    sf::RectangleShape messageBox;
    Scene currentScene;
    Scene &selectedScene;

    void initializeComponents();
};

} // namespace graphics::components

#endif // ERRORPOPUP_HPP