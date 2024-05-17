#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include "../analysis/analysis.hpp"
#include "../analysis/results.hpp"
#include "../graphics/components/button/button.hpp"
#include "../graphics/components/legend/legend.hpp"
#include "../simulation/system.hpp"
#include "appStyle.hpp"
#include "components/textInput/textInput.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class AnalysisWindow {
  public:
    AnalysisWindow(std::shared_ptr<sf::RenderWindow> window,
                   std::shared_ptr<System<float>> system, Scene &selectedScene);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<System<float>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;
    Button menuButton;
    Button analyzeButton;
    Legend<float> resultsPanel;
    std::array<TextInput, 4> textInputs;

    sf::Font font;
    sf::Text title;
    sf::RectangleShape titleBox;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    sf::RectangleShape inputBox;

    sf::Text resultsText;

    void initializeComponents();
};

#endif