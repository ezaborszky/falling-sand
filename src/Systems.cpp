#include "Systems.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
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

void drawMap(int height, int width, TileMap::cellType (&grid)[500][500],
             EntityMap &entMap, EntityManager &manager, int &frame) {
  for (int x = 0; x < TileMap::WIDTH; ++x) {
    for (int y = 0; y < TileMap::HEIGHT; ++y) {

      if (grid[x][y] == TileMap::SAND && (!entMap[{x, y}])) {
        auto e = manager.addEntity(1, x, y);
        e->compShape =
            std::make_shared<Shape>(sf::Vector2f(1024.f / 500, 1024.f / 500));
        entMap[{x, y}] = e;
        float xPos = (1024.f / 500) * x;
        float yPos = (1024.f / 500) * y;
        sf::Vector2f posVec = {xPos, yPos};
        e->compShape->circleShape.setPosition(posVec);
        e->compShape->circleShape.setFillColor(sf::Color(153, 153, 0));
      }
    }
  }
}

void setCell(sf::RenderWindow &window, sf::Event &event,
             TileMap::cellType (&grid)[500][500]) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    int xcor, ycor;
    float cellSize = static_cast<float>(window.getSize().x) / 500;
    xcor = sf::Mouse::getPosition(window).x;
    ycor = sf::Mouse::getPosition(window).y;

    int x = static_cast<int>(xcor / cellSize + 0.5f);
    int y = static_cast<int>(ycor / cellSize + 0.5f);

    if (x >= 0 && x < 500 && y >= 0 && y < 500) {
      if (grid[x][y] == TileMap::EMPTY)
        grid[x][y] = TileMap::SAND;
    }
  }
}
