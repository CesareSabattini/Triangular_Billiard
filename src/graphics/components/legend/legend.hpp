#ifndef LEGEND_HPP
#define LEGEND_HPP

#include "legendItem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace graphics::components {
template <typename T> class Legend : public sf::Drawable {
  public:
    Legend(const std::vector<LegendItem<T>> &p_items,
           const sf::Vector2f &p_size, const sf::Color &p_color,
           const std::shared_ptr<sf::Font> p_font,
           const sf::Color &p_textColor = sf::Color::Black);
    ~Legend();

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    void setPosition(const sf::Vector2f &position);
    void setSize(const sf::Vector2f &size);

    void addItem(const LegendItem<T> &item);

    void removeItem(const std::string &name);

    void clearItems();

    void addItems(const std::vector<LegendItem<T>> &newItems);

  protected:
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;

  private:
    std::shared_ptr<sf::Font> font;
    sf::RectangleShape background;
    std::vector<sf::Text> texts;
    std::vector<LegendItem<T>> items;
    sf::Color textColor;
};

} // namespace graphics::components

#endif
