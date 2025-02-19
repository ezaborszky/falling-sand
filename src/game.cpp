#include "game.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"
#include "Systems.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <memory>
const int WIDTH = 1024;
const int HEIGHT = 1024;
unsigned int currentFrame = 1;
unsigned int lastFrame = 1;
TileMap::cellType state;
Game::Game() {
  m_window.create(sf::VideoMode(WIDTH, HEIGHT), "Sand");
  m_window.setFramerateLimit(121);
}

void Game::run() {

  EntityManager manager;
  TileMap tMap;
  while (m_window.isOpen()) {
    sf::Event event;
    drawMap(WIDTH, HEIGHT, tMap, manager.entMap, manager);
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Space) {
        ++currentFrame;
      }
      setState(event, state);
      setCell(m_window, event, tMap, state, manager.entMap);
    }
    moveCells(manager.entMap, tMap, currentFrame, lastFrame);
    renderObjects(m_window, manager.entMap);
    //++currentFrame;
  }
}
