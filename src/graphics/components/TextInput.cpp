#include "TextInput.hpp"

TextInput::TextInput(sf::Vector2f position, sf::Vector2f size,
                     unsigned int fontSize, const sf::Color backgroundColor,
                     const sf::Color &p_textColor)
    : isFocused(false) {
    inputBox.setPosition(position);
    inputBox.setSize(size);
    inputBox.setFillColor(backgroundColor);

    font.loadFromFile("../resources/theme_font.ttf");

    displayText.setFont(font);
    displayText.setCharacterSize(fontSize);
    displayText.setFillColor(p_textColor);
    displayText.setPosition(position + sf::Vector2f(5.f, 5.f));
}

void TextInput::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::TextEntered && isFocused) {
        if (event.text.unicode == '\b') {
            if (!text.empty()) {
                text.pop_back();
            }
        } else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            text.push_back(static_cast<char>(event.text.unicode));
        }
        displayText.setString(text);
    }
}

void TextInput::draw(sf::RenderWindow &window) {
    window.draw(inputBox);
    window.draw(displayText);
}

const std::string &TextInput::getText() const { return text; }

void TextInput::setText(const std::string &newText) {
    text = newText;
    displayText.setString(text);
}

void TextInput::setPosition(sf::Vector2f position) {
    inputBox.setPosition(position);
    displayText.setPosition(position + sf::Vector2f(5.f, 5.f));
}

void TextInput::setSize(sf::Vector2f size) { inputBox.setSize(size); }

void TextInput::setFocus(bool hasFocus) {
    this->isFocused = hasFocus;
    inputBox.setFillColor(hasFocus ? sf::Color::Green : sf::Color::Red);
}
