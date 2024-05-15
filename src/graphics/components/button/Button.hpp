#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button {
  public:
    Button(sf::Vector2f p_position, sf::Vector2f p_size, sf::Color p_color,
           sf::Color p_hoverColor, sf::Color p_clickColor,
           sf::Color p_textColor, sf::Font &p_font, std::string p_text,
           unsigned int p_textSize);
    void draw(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    bool isClicked();
    void setText(std::string p_text);

    void setPosition(const sf::Vector2f &position);

    void setSize(const sf::Vector2f &size);

    sf::FloatRect getGlobalBounds();

  private:
    sf::RectangleShape button;
    sf::Color color;
    sf::Color hoverColor;
    sf::Color clickColor;
    sf::Text text;
    bool isHover;
    bool isClick;
};

#endif