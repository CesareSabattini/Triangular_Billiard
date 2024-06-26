#include "legend.hpp"

template <typename T>
graphics::components::Legend<T>::Legend(
    const std::vector<LegendItem<T>> &p_items, const sf::Vector2f &p_size,
    const sf::Color &p_color, const std::shared_ptr<sf::Font> p_font,
    const sf::Color &p_textColor)
    : font(p_font), items(p_items), textColor(p_textColor) {

  background.setSize(p_size);
  background.setFillColor(p_color);

  for (const auto &item : items) {
    sf::Text text;
    text.setFont(*font);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(item.getPrecision())
        << item.getValue();

    text.setString(item.getName() + ": " + oss.str() + " " + item.getUnit());
    text.setCharacterSize(20);
    text.setFillColor(textColor);
    texts.push_back(text);
  }
}

template <typename T> graphics::components::Legend<T>::~Legend() {}

template <typename T>
void graphics::components::Legend<T>::draw(sf::RenderTarget &target,
                                           sf::RenderStates states) const {
  target.draw(background, states);
  for (const auto &text : texts) {
    target.draw(text, states);
  }
}

template <typename T>
sf::Vector2f graphics::components::Legend<T>::getPosition() const {

  return background.getPosition();
}

template <typename T>
sf::Vector2f graphics::components::Legend<T>::getSize() const {

  return background.getSize();
}

template <typename T>
void graphics::components::Legend<T>::setPosition(
    const sf::Vector2f &position) {
  background.setPosition(position);
  float heightPortion =
      background.getSize().y / static_cast<float>(texts.size());
  for (int i = 0; i < static_cast<int>(texts.size()); i++) {
    texts[static_cast<std::vector<sf::Text>::size_type>(i)].setPosition(
        position.x + 10,
        position.y + static_cast<float>(i) * heightPortion + 10);
  }
}

template <typename T>
void graphics::components::Legend<T>::setSize(const sf::Vector2f &size) {
  background.setSize(size);
  float heightPortion = size.y / static_cast<float>(texts.size());
  for (int i = 0; i < static_cast<int>(texts.size()); i++) {
    texts[static_cast<std::vector<sf::Text>::size_type>(i)].setPosition(
        background.getPosition().x + 10,
        background.getPosition().y + static_cast<float>(i) * heightPortion +
            10);
  }
}

template <typename T>
void graphics::components::Legend<T>::addItem(const LegendItem<T> &item) {
  sf::Text text;
  text.setFont(*font);
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(item.getPrecision())
      << item.getValue();

  text.setString(item.getName() + ": " + oss.str() + " " + item.getUnit());
  text.setCharacterSize(20);
  text.setFillColor(textColor);
  texts.push_back(text);
  items.push_back(item);
}

template <typename T>
void graphics::components::Legend<T>::removeItem(const std::string &name) {
  for (int i = 0; i < static_cast<int>(items.size()); i++) {
    if (items[static_cast<std::allocator<LegendItem<double>>::size_type>(i)]
            .getName() == name) {
      items.erase(items.begin() + i);
      texts.erase(texts.begin() + i);
      break;
    }
  }
}

template <typename T> void graphics::components::Legend<T>::clearItems() {
  items.clear();
  texts.clear();
}

template <typename T>
void graphics::components::Legend<T>::addItems(
    const std::vector<LegendItem<T>> &newItems) {
  for (const auto &item : newItems) {
    addItem(item);
  }
}

template class graphics::components::Legend<int>;
template class graphics::components::Legend<float>;
template class graphics::components::Legend<double>;