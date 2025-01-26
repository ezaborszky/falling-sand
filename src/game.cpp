#include "game.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"
#include "Systems.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>

Game::Game() {
  m_window.create(sf::VideoMode(1280, 1024), "Sand");
  m_window.setFramerateLimit(60);
}

void Game::run() {

  EntityManager manager;
  auto ent = manager.addEntity(1);
  ent->compShape = std::make_shared<Shape>(33, 5);
  manager.Update();
  while (m_window.isOpen()) {
    sf::Event event;

    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }
    }

    renderObjects(m_window, manager.m_entities);
  }
}
