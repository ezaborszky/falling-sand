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
#include <utility>

void renderObjects(sf::RenderWindow &window, EntityMap &entMap) {
  window.clear();
  for (const auto &pair : entMap) {
    auto a = pair.second;
    window.draw(a->compShape->circleShape);
  }
  window.display();
}

void drawMap(int height, int width, TileMap &tileMap, EntityMap &entMap,
             EntityManager &manager) {
  for (auto a : tileMap.m_activeCells) {
    int x = a.first;
    int y = a.second;

    if (tileMap.grid[x][y] == TileMap::SAND && (!entMap[{x, y}])) {
      auto e = manager.addEntity(1, x, y);
      e->compShape = std::make_shared<Shape>(
          sf::Vector2f(1024.f / tileMap.WIDTH, 1024.f / tileMap.WIDTH));
      entMap[{x, y}] = e;
      int size = entMap.size();
      // std::cout << size << "asd \n";
      float xPos = (1024.f / tileMap.WIDTH) * x;
      float yPos = (1024.f / tileMap.WIDTH) * y;
      sf::Vector2f posVec = {xPos, yPos};
      e->compShape->circleShape.setPosition(posVec);
      e->compShape->circleShape.setFillColor(sf::Color(153, 153, 0));
    }
  }
}

void setCell(sf::RenderWindow &window, sf::Event &event, TileMap &tileMap) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    int xcor, ycor;
    float cellSize = static_cast<float>(window.getSize().x) / tileMap.WIDTH;
    xcor = sf::Mouse::getPosition(window).x;
    ycor = sf::Mouse::getPosition(window).y;

    int x = static_cast<int>(xcor / cellSize + 0.5f);
    int y = static_cast<int>(ycor / cellSize + 0.5f);

    if (x >= 0 && x < tileMap.WIDTH && y >= 0 && y < tileMap.WIDTH) {
      if (tileMap.grid[x][y] == TileMap::EMPTY) {
        tileMap.grid[x][y] = TileMap::SAND;
        tileMap.updateCellsList(x, y);
      }
    }
  }
}

void moveCells(EntityMap &entMap, TileMap &tileMap, unsigned int &currentFrame,
               unsigned int &lastFrame) {
  if (currentFrame - lastFrame > 3) {

    for (auto cell : tileMap.m_activeCells) {
      if (cell.second < tileMap.WIDTH - 2 &&
          tileMap.grid[cell.first][cell.second + 1] == TileMap::EMPTY) {
        tileMap.grid[cell.first][cell.second] = TileMap::EMPTY;
        tileMap.grid[cell.first][cell.second + 1] = TileMap::SAND;
        entMap.erase({cell.first, cell.second});
        tileMap.m_cellsToAdd.push_back(
            std::pair<int, int>(cell.first, cell.second + 1));
      }
    }

    for (auto e : tileMap.m_cellsToAdd) {
      tileMap.m_activeCells.push_back(e);
    }
    auto del = std::remove_if(
        tileMap.m_activeCells.begin(), tileMap.m_activeCells.end(),
        [&tileMap](const std::pair<int, int> &cell) {
          return tileMap.grid[cell.first][cell.second] == TileMap::EMPTY;
        });
    tileMap.m_activeCells.erase(del, tileMap.m_activeCells.end());

    std::cout << tileMap.m_activeCells.size() << "\n";
    tileMap.m_cellsToAdd.clear();

    lastFrame = currentFrame;
  }
}
