#include "Button.hpp"

Button::Button(sf::Vector2f p_position, sf::Vector2f p_size, sf::Color p_color,
               sf::Color p_hoverColor, sf::Color p_clickColor,
               sf::Color p_textColor, std::string p_text,
               unsigned int p_textSize)
    : color(p_color), hoverColor(p_hoverColor), clickColor(p_clickColor),
      isHover(false), isClick(false) {
    button.setPosition(p_position);
    button.setSize(p_size);
    button.setFillColor(color);

    if (!font.loadFromFile("../resources/theme_font.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    text.setFont(font);
    text.setString(p_text);
    text.setCharacterSize(p_textSize);
    text.setFillColor(p_textColor);
    text.setPosition(
        p_position.x + p_size.x / 2 - text.getGlobalBounds().width / 2,
        p_position.y + p_size.y / 2 - text.getGlobalBounds().height / 2);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
}

void Button::update(sf::RenderWindow &window) {
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

void Button::setText(std::string p_text) {
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

sf::FloatRect Button::getGlobalBounds() { return button.getGlobalBounds(); }