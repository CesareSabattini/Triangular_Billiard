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
    Scene &selectedScene;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<System<double>> system;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape titleBox;

    Button menuButton;

    Button analyzeButton;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    sf::RectangleShape inputBox;
    std::array<TextInput, 4> textInputs;

    sf::Text resultsText;
    Legend<double> resultsPanel;

    void initializeComponents();
};

#endif