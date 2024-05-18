#include "textInput.hpp"

TextInput::TextInput(sf::Vector2f position, sf::Vector2f size,
                     unsigned int fontSize, const sf::Color p_backgroundColor,
                     std::shared_ptr<sf::Font> p_font,
                     const sf::Color &p_textColor,
                     const std::string &p_propName,
                     const std::string &p_defaultText)
    : isFocused(false), font(p_font), font2(p_font),
      backgroundColor(p_backgroundColor), textColor(p_textColor),
      propName(p_propName), defaultText(p_defaultText) {

    propText.setFont(*font2);
    propText.setCharacterSize(fontSize);
    propText.setFillColor(textColor);
    propText.setPosition(position);
    propText.setString(propName);

    float verticalOffset = propText.getGlobalBounds().height + 5.f;

    displayText.setFont(*font);
    displayText.setCharacterSize(fontSize);
    displayText.setFillColor(textColor);

    inputBox.setPosition(position.x, position.y + verticalOffset);
    inputBox.setSize(sf::Vector2f(size.x, size.y - verticalOffset));
    inputBox.setFillColor(backgroundColor);

    displayText.setPosition(
        position.x, inputBox.getPosition().y + inputBox.getSize().y / 2 -
                        displayText.getGlobalBounds().height / 2);

    text = defaultText;
    displayText.setString(text);
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
    window.draw(propText);
    window.draw(displayText);
}

const std::string TextInput::getText() const { return text; }

void TextInput::setText(const std::string &newText) {
    text = newText;
    displayText.setString(text);
}

void TextInput::setPosition(sf::Vector2f position) {
    propText.setPosition(position);
    float verticalOffset = propText.getGlobalBounds().height + 5;
    inputBox.setPosition(position.x, position.y + verticalOffset);
    displayText.setPosition(
        position.x, inputBox.getPosition().y + inputBox.getSize().y / 2 -
                        displayText.getGlobalBounds().height / 2);
}

void TextInput::setSize(sf::Vector2f size) {
    displayText.setCharacterSize(static_cast<unsigned int>(size.y / 4));
    sf::Vector2f inputBoxSize(size.x,
                              size.y - propText.getGlobalBounds().height - 5);
    inputBox.setSize(inputBoxSize);
    displayText.setPosition(inputBox.getPosition().x,
                            inputBox.getPosition().y +
                                inputBox.getSize().y / 2 -
                                displayText.getGlobalBounds().height / 2);
}

void TextInput::setFocus(bool hasFocus) {
    this->isFocused = hasFocus;
    inputBox.setFillColor(hasFocus ? sf::Color(backgroundColor.Cyan)
                                   : sf::Color(backgroundColor));
    if (displayText.getString() == defaultText) {
        if (hasFocus) {
            text = "";
        } else {
            text = defaultText;
        }
    } else if (!hasFocus && text.empty()) {
        text = defaultText;
    }
    displayText.setString(text);
}
