#include "Systems.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

void renderObjects(sf::RenderWindow &window, EntityMap &entMap) {
  window.clear();
  for (const auto &pair : entMap) {
    auto a = pair.second;
    window.draw(a->compShape->circleShape);
  }
  window.display();
}

void drawMap(int height, int width, TileMap::cellType (&grid)[100][100],
             EntityMap &entMap, EntityManager &manager) {
  for (int x = 0; x < TileMap::WIDTH; ++x) {
    for (int y = 0; y < TileMap::HEIGHT; ++y) {
      if (grid[x][y] == TileMap::SAND && (!entMap[{x, y}])) {
        auto e = manager.addEntity(1, x, y);
        e->compShape = std::make_shared<Shape>(1024 / 100, 4);
        entMap[{x, y}] = e;
        float xPos = (1280 / 100) * x;
        float yPos = (1024 / 100) * y;
        sf::Vector2f posVec = {xPos, yPos};
        e->compShape->circleShape.setPosition(posVec);
        e->compShape->circleShape.setFillColor(sf::Color::Green);
        e->compShape->circleShape.setRotation(45.f);
        std::cout << "asd" << std::endl;
      }
    }
  }
}
