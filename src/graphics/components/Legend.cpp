#include "Legend.hpp"

template <typename T>
Legend<T>::Legend(std::vector<LegendItem<T>> p_items, sf::Vector2f p_size,
                  sf::Color p_color)
    : items(p_items) {

    background.setSize(p_size);
    background.setFillColor(p_color);

    if (!font.loadFromFile("../resources/theme_font.ttf")) {

        std::cerr << "Error loading font" << std::endl;
    }

    for (const auto &item : items) {
        sf::Text text;
        text.setFont(font);
        text.setString(item.getName() + ": " + std::to_string(item.getValue()) +
                       " " + item.getUnit());
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        texts.push_back(text);
    }
}

template <typename T> Legend<T>::~Legend() {}

template <typename T>
void Legend<T>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    for (const auto &text : texts) {
        target.draw(text, states);
    }
}

template <typename T>
void Legend<T>::setPosition(const sf::Vector2f &position) {
    background.setPosition(position);
    float heightPortion = background.getSize().y / texts.size();
    for (int i = 0; i < texts.size(); i++) {
        texts[i].setPosition(position.x + 10,
                             position.y + i * heightPortion + 10);
    }
}

template class Legend<int>;
template class Legend<float>;
template class Legend<double>;