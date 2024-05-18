#include "appStyle.hpp"

namespace AppStyle {

sf::Color Colors::bgCyan = sf::Color(2, 138, 160);
sf::Color Colors::cream = sf::Color(246, 250, 222);
sf::Color Colors::darkGreen = sf::Color(57, 165, 93);
sf::Color Colors::opaqueBlack = sf::Color(0, 0, 0, 150);

AppStyle::AppStyle() : font(std::make_shared<sf::Font>()) {
    if (!font->loadFromFile("../resources/theme_font.ttf")) {
        throw std::runtime_error("Cannot load font");
    }
}

AppStyle::~AppStyle() {}

std::shared_ptr<sf::Font> AppStyle::getFont() const { return font; }

} // namespace AppStyle
