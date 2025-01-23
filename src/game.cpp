#include "game.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

Game::Game() {
  m_window.create(sf::VideoMode(1280, 1024), "Sand");
  m_window.setFramerateLimit(60);
}

void Game::run() {
  sf::CircleShape myShape(33.f);
  while (m_window.isOpen()) {
    sf::Event event;

    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }
    }

    m_window.clear();
    m_window.draw(myShape);
    m_window.display();
  }
}
