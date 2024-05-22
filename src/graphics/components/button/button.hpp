#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace graphics::components {
class Button {
  public:
    Button(const sf::Vector2f &p_position, const sf::Vector2f &p_size,
           const sf::Color &p_color, const sf::Color &p_hoverColor,
           const sf::Color &p_clickColor, const sf::Color &p_textColor,
           const std::string &p_text, const unsigned int p_textSize,
           std::shared_ptr<sf::Font> font);

    Button() = default;
    void draw(sf::RenderWindow &window) const;
    void update(const sf::RenderWindow &window);
    bool isClicked();
    void setText(const std::string p_text);

    void setPosition(const sf::Vector2f &position);

    void setSize(const sf::Vector2f &size);

    sf::FloatRect getGlobalBounds() const;

  private:
    std::shared_ptr<sf::Font> font;
    sf::RectangleShape button;
    sf::Color color;
    sf::Color hoverColor;
    sf::Color clickColor;
    sf::Text text;
    bool isHover;
    bool isClick;
};

} // namespace graphics::components

#endif