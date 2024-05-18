#include "button.hpp"

Button::Button(const sf::Vector2f &p_position, const sf::Vector2f &p_size,
               const sf::Color &p_color, const sf::Color &p_hoverColor,
               const sf::Color &p_clickColor, const sf::Color &p_textColor,
               const std::string &p_text, const unsigned int p_textSize,
               std::shared_ptr<sf::Font> p_font)
    : font(p_font), color(p_color), hoverColor(p_hoverColor),
      clickColor(p_clickColor), isHover(false), isClick(false) {
    button.setPosition(p_position);
    button.setSize(p_size);
    button.setFillColor(color);

    text.setFont(*font.get());
    text.setString(p_text);
    text.setCharacterSize(p_textSize);
    text.setFillColor(p_textColor);
    text.setPosition(
        p_position.x + p_size.x / 2 - text.getGlobalBounds().width / 2,
        p_position.y + p_size.y / 2 - text.getGlobalBounds().height / 2);
}

void Button::draw(sf::RenderWindow &window) const {
    window.draw(button);
    window.draw(text);
}

void Button::update(const sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                          static_cast<float>(mousePos.y))) {
        button.setFillColor(hoverColor);
        isHover = true;
    } else {
        button.setFillColor(color);
        isHover = false;
    }
}

bool Button::isClicked() {
    if (isHover && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isClick = true;
    } else {
        isClick = false;
    }
    return isClick;
}

void Button::setText(const std::string p_text) {
    text.setString(p_text);
    text.setPosition(button.getPosition().x + button.getSize().x / 2 -
                         text.getGlobalBounds().width / 2,
                     button.getPosition().y + button.getSize().y / 2 -
                         text.getGlobalBounds().height / 2);
}

void Button::setPosition(const sf::Vector2f &position) {
    button.setPosition(position);
    text.setPosition(position.x + button.getSize().x / 2 -
                         text.getGlobalBounds().width / 2,
                     position.y + button.getSize().y / 2 -
                         text.getGlobalBounds().height / 2);
}

void Button::setSize(const sf::Vector2f &size) {
    button.setSize(size);
    text.setPosition(button.getPosition().x + button.getSize().x / 2 -
                         text.getGlobalBounds().width / 2,
                     button.getPosition().y + button.getSize().y / 2 -
                         text.getGlobalBounds().height / 2);
}

sf::FloatRect Button::getGlobalBounds() const {
    return button.getGlobalBounds();
}
