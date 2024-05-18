#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class TextInput {
  public:
    TextInput(sf::Vector2f position, sf::Vector2f size, unsigned int fontSize,
              const sf::Color backgroundColor, std::shared_ptr<sf::Font> p_font,
              const sf::Color &textColor = sf::Color::Black,
              const std::string &propName = "",
              const std::string &defaultText = "");

    void handleEvent(const sf::Event &event);
    void draw(sf::RenderWindow &window);
    const std::string getText() const;
    void setText(const std::string &text);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setFocus(bool hasFocus);

    sf::RectangleShape inputBox;
    bool isFocused;

  private:
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<sf::Font> font2;
    sf::Text propText;
    sf::Text displayText;
    sf::Color backgroundColor;
    sf::Color textColor;
    std::string text;
    std::string propName;
    std::string defaultText;
};

#endif
