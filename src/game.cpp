#include "game.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"
#include "Systems.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
const int WIDTH = 1280;
const int HEIGHT = 1024;

Game::Game() {
  m_window.create(sf::VideoMode(WIDTH, HEIGHT), "Sand");
  m_window.setFramerateLimit(60);
}

void Game::run() {

  EntityManager manager;
  TileMap tMap;
  tMap.grid[22][22] = TileMap::SAND;
  tMap.grid[23][23] = TileMap::SAND;
  while (m_window.isOpen()) {
    sf::Event event;
    drawMap(100, 100, tMap.grid, manager.entMap, manager);
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }
    }

    renderObjects(m_window, manager.entMap);
  }
}
