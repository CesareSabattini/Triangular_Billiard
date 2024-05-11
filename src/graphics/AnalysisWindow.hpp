#ifndef ANALYSISWINDOW_HPP
#define ANALYSISWINDOW_HPP

#include "../analysis/Analysis.hpp"
#include "../analysis/Results.hpp"
#include "../graphics/components/Legend.hpp"
#include "../simulation/System.hpp"
#include "Scene.hpp"
#include "components/TextInput.hpp"
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

    sf::RectangleShape menuButton;
    sf::Text menuButtonText;

    sf::RectangleShape analyzeButton;
    sf::Text analyzeButtonText;

    sf::Texture backgroundTexture;
    sf::Sprite bg;

    sf::RectangleShape inputBox;
    std::array<TextInput, 4> textInputs;

    sf::RectangleShape resultsBox;
    sf::Text resultsText;
    Legend<double> resultsPanel;

    void initializeComponents();
};

#endif