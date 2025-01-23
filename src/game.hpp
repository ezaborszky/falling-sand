#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
class Game {
public:
  sf::RenderWindow m_window;
  Game();
  void run();
  void sRender(sf::RenderWindow &window);
};
