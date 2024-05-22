#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include "../../analysis/analysis.hpp"
#include "../../analysis/parameters.hpp"
#include "../../analysis/results.hpp"
#include "../../simulation/system.hpp"
#include "../components/button/button.hpp"
#include "../components/legend/legend.hpp"
#include "../components/textInput/textInput.hpp"
#include "../style/appStyle.hpp"
#include "../utils/scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics::scenes {

class AnalysisWindow {
  public:
    AnalysisWindow(std::shared_ptr<sf::RenderWindow> window,
                   std::shared_ptr<simulation::System<float>> system,
                   Scene &selectedScene, const std::shared_ptr<sf::Font> font);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<simulation::System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;
    graphics::components::Button menuButton;
    graphics::components::Button analyzeButton;
    graphics::components::Legend<float> resultsPanel;
    std::array<graphics::components::TextInput, 8> textInputs;

    sf::Text title;
    sf::RectangleShape titleBox;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    sf::RectangleShape inputBox;

    sf::Text resultsText;

    void initializeComponents();
};

} // namespace graphics::scenes

#endif