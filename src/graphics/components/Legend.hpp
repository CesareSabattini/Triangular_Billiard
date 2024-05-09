#ifndef LEGEND_HPP
#define LEGEND_HPP

#include "LegendItem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

template <typename T> class Legend : public sf::Drawable {
  public:
    Legend(std::vector<LegendItem<T>> items, sf::Vector2f size,
           sf::Color p_color);
    ~Legend();

    void setPosition(const sf::Vector2f &position);

    void addItem(const LegendItem<T> &item) {
        sf::Text text;
        text.setFont(font);
        text.setString(item.getName() + ": " + std::to_string(item.getValue()) +
                       " " + item.getUnit());
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        texts.push_back(text);
        items.push_back(item);
    }

  protected:
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;

  private:
    sf::RectangleShape background;
    std::vector<sf::Text> texts;
    std::vector<LegendItem<T>> items;
    sf::Font font;
};

#endif
