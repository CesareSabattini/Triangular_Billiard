#include "errorPopup.hpp"

graphics::components::ErrorPopup::ErrorPopup(
    std::shared_ptr<sf::RenderWindow> p_window,
    const std::shared_ptr<sf::Font> p_font, const std::string &err_text,
    Scene &p_selectedScene)
    : font(p_font), window(p_window),
      okButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f),
               appStyle::Colors::darkGreen, appStyle::Colors::darkGreen.Blue,
               appStyle::Colors::darkGreen.Black, appStyle::Colors::cream, "OK",
               20, font),
      currentScene(p_selectedScene), selectedScene(p_selectedScene) {

  message.setString("Error: \n " + err_text);

  initializeComponents();
}

void graphics::components::ErrorPopup::initializeComponents() {
  message.setFont(*font);
  message.setCharacterSize(window->getSize().x / 25);
  message.setFillColor(appStyle::Colors::bgCyan);
  message.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                          message.getGlobalBounds().width / 2.f,

                      static_cast<float>(window->getSize().y) / 2.f -
                          message.getGlobalBounds().height / 2.f);

  messageBox.setSize(sf::Vector2f(message.getGlobalBounds().width + 50.f,
                                  message.getGlobalBounds().height + 50.0f));
  messageBox.setFillColor(appStyle::Colors::cream);
  messageBox.setPosition(static_cast<float>(window->getSize().x) / 2.f -
                             messageBox.getGlobalBounds().width / 2.f,
                         message.getPosition().y);

  okButton.setSize(
      sf::Vector2f(static_cast<float>(window->getSize().x) / 10.f, 60.f));
  okButton.setPosition(
      {static_cast<float>(window->getSize().x) / 2.f -
           okButton.getGlobalBounds().width / 2,
       messageBox.getPosition().y + messageBox.getSize().y + 20});
}

void graphics::components::ErrorPopup::draw() {
  window->draw(messageBox);
  window->draw(message);
  okButton.draw(*window);
}

void graphics::components::ErrorPopup::processEvents() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window->close();

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

      if (okButton.getGlobalBounds().contains(
              static_cast<float>(mousePosition.x),
              static_cast<float>(mousePosition.y))) {
        selectedScene = currentScene;
      }
    }
  }
}