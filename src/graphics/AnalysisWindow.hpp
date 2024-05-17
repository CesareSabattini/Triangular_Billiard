#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include "../analysis/Analysis.hpp"
#include "../analysis/Results.hpp"
#include "../graphics/components/button/Button.hpp"
#include "../graphics/components/legend/Legend.hpp"
#include "../simulation/System.hpp"
#include "AppStyle.hpp"
#include "Scene.hpp"
#include "components/textInput/TextInput.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class AnalysisWindow {
  public:
    AnalysisWindow(std::shared_ptr<sf::RenderWindow> window,
                   std::shared_ptr<System<double>> system,
                   Scene &selectedScene);
    void draw();
    void processEvents();

  private:
    std::shared_ptr<System<double>> system;
    std::shared_ptr<sf::RenderWindow> window;
    Scene &selectedScene;
    Button menuButton;
    Button analyzeButton;
    Legend<double> resultsPanel;
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