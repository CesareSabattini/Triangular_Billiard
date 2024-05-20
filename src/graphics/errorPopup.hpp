#ifndef ERRORPOPUP_HPP
#define ERRORPOPUP_HPP

#include "appStyle.hpp"
#include "components/button/button.hpp"
#include "scene.hpp"

#include <SFML/Graphics.hpp>

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

#endif // ERRORPOPUP_HPP