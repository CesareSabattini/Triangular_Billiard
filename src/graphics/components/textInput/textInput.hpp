#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics::components {
class TextInput {
  public:
    TextInput(const sf::Vector2f &position, const sf::Vector2f &size,
              const unsigned int fontSize, const sf::Color &backgroundColor,
              const std::shared_ptr<sf::Font> p_font,
              const sf::Color &textColor = sf::Color::Black,
              const std::string &propName = "",
              const std::string &defaultText = "");
    ~TextInput();

    void handleEvent(const sf::Event &event);
    void draw(sf::RenderWindow &window);
    const std::string getText() const;
    void setText(const std::string &text);
    void setPosition(const sf::Vector2f &position);
    void setSize(const sf::Vector2f &size);
    void setFocus(const bool hasFocus);

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
} // namespace graphics::components

#endif
