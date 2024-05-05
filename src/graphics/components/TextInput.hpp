#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <SFML/Graphics.hpp>

class TextInput {
  public:
    TextInput(sf::Vector2f position, sf::Vector2f size, unsigned int fontSize,
              const sf::Color backgroundColor,
              const sf::Color &textColor = sf::Color::Black,
              const std::string &defaultText = "");

    void handleEvent(const sf::Event &event);
    void draw(sf::RenderWindow &window);
    const std::string &getText() const;
    void setText(const std::string &text);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setFocus(bool hasFocus);

    sf::RectangleShape inputBox;
    bool isFocused;

  private:
    sf::Text displayText;
    sf::Color textColor;
    std::string text;
    std::string defaultText;

    sf::Font font;
};

#endif
