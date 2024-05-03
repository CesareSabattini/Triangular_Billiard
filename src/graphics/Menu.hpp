// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "../simulation/System.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Menu {
  public:
    Menu(std::shared_ptr<sf::RenderWindow> window,
         std::shared_ptr<System<double>> system);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape inputBox;
    sf::RectangleShape startButton;
    sf::Text startButtonText;

    void initializeComponents();
};

#endif
