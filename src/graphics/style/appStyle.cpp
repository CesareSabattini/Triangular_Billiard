#include "appStyle.hpp"

sf::Color appStyle::Colors::bgCyan = sf::Color(2, 138, 160);
sf::Color appStyle::Colors::cream = sf::Color(246, 250, 222);
sf::Color appStyle::Colors::darkGreen = sf::Color(57, 165, 93);
sf::Color appStyle::Colors::opaqueBlack = sf::Color(0, 0, 0, 150);

appStyle::AppStyle::AppStyle() : font(std::make_shared<sf::Font>()) {
    if (!font->loadFromFile("../../resources/theme_font.ttf")) {
        throw std::runtime_error("Cannot load font");
    }
}

appStyle::AppStyle::~AppStyle() {}

const std::shared_ptr<sf::Font> appStyle::AppStyle::getFont() const {
    return font;
}
