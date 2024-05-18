#ifndef APP_STYLE_HPP
#define APP_STYLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace AppStyle {

struct Colors {

    static sf::Color bgCyan;
    static sf::Color cream;
    static sf::Color darkGreen;
    static sf::Color opaqueBlack;
};

class AppStyle {
  public:
    AppStyle();
    ~AppStyle();
    std::shared_ptr<sf::Font> getFont() const;

  private:
    std::shared_ptr<sf::Font> font;
};

} // namespace AppStyle

#endif // APP_STYLE_HPP
