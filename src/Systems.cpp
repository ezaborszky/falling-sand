#include "Systems.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

void renderObjects(sf::RenderWindow &window, EntityMap &entMap) {
  window.clear();
  for (const auto &pair : entMap) {
    auto a = pair.second;
    window.draw(a->compShape->circleShape);
  }
  window.display();
}

void setState(sf::Event event, TileMap::cellType &type) {
  if (event.key.code == sf::Keyboard::Num1)
    type = TileMap::SAND;
  if (event.key.code == sf::Keyboard::Num2)
    type = TileMap::WATER;
  if (event.key.code == sf::Keyboard::Num3)
    type = TileMap::ROCK;
}

void drawMap(int height, int width, TileMap &tileMap, EntityMap &entMap,
             EntityManager &manager) {
  for (auto a : tileMap.m_activeCells) {
    int x = a.first;
    int y = a.second;

    if (tileMap.grid[x][y] == TileMap::SAND && (!entMap[{x, y}])) {
      auto e = manager.addEntity(1, x, y);
      e->compShape = std::make_shared<Shape>(
          sf::Vector2f(float(width) / tileMap.WIDTH, 1024.f / tileMap.WIDTH));
      entMap[{x, y}] = e;
      int size = entMap.size();
      // std::cout << size << "asd \n";
      float xPos = (float(width) / tileMap.WIDTH) * x;
      float yPos = (float(width) / tileMap.WIDTH) * y;
      sf::Vector2f posVec = {xPos, yPos};
      e->compShape->circleShape.setPosition(posVec);
      e->compShape->circleShape.setFillColor(sf::Color((153), x * 2, 0));
    } else if (tileMap.grid[x][y] == TileMap::WATER && (!entMap[{x, y}])) {
      auto e = manager.addEntity(1, x, y);
      e->compShape = std::make_shared<Shape>(
          sf::Vector2f(float(width) / tileMap.WIDTH, 1024.f / tileMap.WIDTH));
      entMap[{x, y}] = e;
      int size = entMap.size();
      // std::cout << size << "asd \n";
      float xPos = (float(width) / tileMap.WIDTH) * x;
      float yPos = (float(width) / tileMap.WIDTH) * y;
      sf::Vector2f posVec = {xPos, yPos};
      e->compShape->circleShape.setPosition(posVec);
      e->compShape->circleShape.setFillColor(sf::Color(11, 11, 255));
    } else if (tileMap.grid[x][y] == TileMap::ROCK && (!entMap[{x, y}])) {
      auto e = manager.addEntity(1, x, y);
      e->compShape = std::make_shared<Shape>(
          sf::Vector2f(float(width) / tileMap.WIDTH, 1024.f / tileMap.WIDTH));
      entMap[{x, y}] = e;
      int size = entMap.size();
      // std::cout << size << "asd \n";
      float xPos = (float(width) / tileMap.WIDTH) * x;
      float yPos = (float(width) / tileMap.WIDTH) * y;
      sf::Vector2f posVec = {xPos, yPos};
      e->compShape->circleShape.setPosition(posVec);
      e->compShape->circleShape.setFillColor(sf::Color(211, 211, 255));
    }
  }
}

void setCell(sf::RenderWindow &window, sf::Event &event, TileMap &tileMap,
             TileMap::cellType state, EntityMap &entMap) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    int xcor, ycor;
    float cellSize = static_cast<float>(window.getSize().x) / tileMap.WIDTH;
    xcor = sf::Mouse::getPosition(window).x;
    ycor = sf::Mouse::getPosition(window).y;

    int x = static_cast<int>(xcor / cellSize + 0.5f);
    int y = static_cast<int>(ycor / cellSize + 0.5f);

    if (x >= 0 && x < tileMap.WIDTH && y >= 0 && y < tileMap.WIDTH) {
      if (tileMap.grid[x][y] == TileMap::EMPTY) {
        tileMap.grid[x][y] = state;
        tileMap.updateCellsList(x, y);
      }
    }
  } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    int xcor, ycor;
    float cellSize = static_cast<float>(window.getSize().x) / tileMap.WIDTH;
    xcor = sf::Mouse::getPosition(window).x;
    ycor = sf::Mouse::getPosition(window).y;

    int x = static_cast<int>(xcor / cellSize + 0.5f);
    int y = static_cast<int>(ycor / cellSize + 0.5f);

    if (x >= 0 && x < tileMap.WIDTH && y >= 0 && y < tileMap.WIDTH) {
      if (tileMap.grid[x][y] != TileMap::EMPTY) {
        tileMap.grid[x][y] = TileMap::EMPTY;
        entMap.erase({x, y});
      }
    }
  }
}

void moveCells(EntityMap &entMap, TileMap &tileMap, unsigned int &currentFrame,
               unsigned int &lastFrame) {
  if ((++currentFrame) - lastFrame > 2) {

    std::sort(tileMap.m_activeCells.begin(), tileMap.m_activeCells.end(),
              [](const auto &a, const auto &b) { return a.second < b.second; });

    for (auto cell : tileMap.m_activeCells) {
      int x = cell.first;
      int y = cell.second;
      // SAND
      if (tileMap.grid[x][y] == TileMap::SAND) {
        // MOVE DOWN
        if (cell.second < tileMap.WIDTH &&
            tileMap.checkGridCell(x, y + 1, TileMap::EMPTY)) {
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          tileMap.setGridCell(x, y + 1, TileMap::SAND);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(
              std::pair<int, int>(cell.first, cell.second + 1));
          // MOVE LEFT OR RIGHT
        } else if (tileMap.checkGridCell(x - 1, y + 1, TileMap::EMPTY) &&
                   tileMap.checkGridCell(x + 1, y + 1, TileMap::EMPTY) &&
                   tileMap.checkGridCell(x, y + 1, TileMap::SAND)) {
          int modifier = (currentFrame % 2 == 0) ? 1 : -1;
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          tileMap.setGridCell(x + modifier, y + 1, TileMap::SAND);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(
              std::pair<int, int>(x + modifier, y + 1));
          std::cout << tileMap.m_cellsToAdd.size() << std::endl;
        } else if (tileMap.checkGridCell(x, y + 1, TileMap::SAND) &&
                   tileMap.checkGridCell(x - 1, y + 1, TileMap::SAND) &&
                   tileMap.checkGridCell(x + 1, y + 1, TileMap::EMPTY)) {
          tileMap.setGridCell(x + 1, y + 1, TileMap::SAND);
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x + 1, y + 1));
        } else if (tileMap.checkGridCell(x, y + 1, TileMap::SAND) &&
                   tileMap.checkGridCell(x + 1, y + 1, TileMap::SAND) &&
                   tileMap.checkGridCell(x - 1, y + 1, TileMap::EMPTY)) {
          tileMap.setGridCell(x - 1, y + 1, TileMap::SAND);
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x - 1, y + 1));
        } else if (tileMap.checkGridCell(x, y, TileMap::SAND) &&
                   tileMap.checkGridCell(x, y + 1, TileMap::WATER)) {
          tileMap.setGridCell(x, y, TileMap::WATER);
          tileMap.setGridCell(x, y + 1, TileMap::SAND);
          entMap.erase({x, y});
          entMap.erase({x, y + 1});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x, y + 1));
          // tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x, y));
        }
      }

      if (tileMap.grid[x][y] == TileMap::WATER) {
        if (tileMap.checkGridCell(x, y + 1, TileMap::EMPTY) &&
            y < tileMap.WIDTH) {
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          tileMap.setGridCell(x, y + 1, TileMap::WATER);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x, y + 1));
        } else if ((tileMap.grid[x][y + 1] != TileMap::EMPTY) && x > 0 &&
                   x < tileMap.WIDTH &&
                   tileMap.checkGridCell(x - 1, y, TileMap::EMPTY) &&
                   tileMap.checkGridCell(x + 1, y, TileMap::EMPTY)) {
          int modifier = (currentFrame % 2 == 0) ? 1 : -1;
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          tileMap.setGridCell(x + modifier, y, TileMap::WATER);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x + modifier, y));

        } else if ((tileMap.grid[x][y + 1] != TileMap::EMPTY) && x > 0 &&
                   tileMap.checkGridCell(x - 1, y, TileMap::EMPTY)) {
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          tileMap.setGridCell(x - 1, y, TileMap::WATER);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x - 1, y));
        } else if ((tileMap.grid[x][y + 1] != TileMap::EMPTY) &&
                   tileMap.checkGridCell(x + 1, y, TileMap::EMPTY) &&
                   x < tileMap.WIDTH) {
          tileMap.setGridCell(x, y, TileMap::EMPTY);
          tileMap.setGridCell(x + 1, y, TileMap::WATER);
          entMap.erase({x, y});
          tileMap.m_cellsToAdd.push_back(std::pair<int, int>(x + 1, y));
        }
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
    tileMap.m_cellsToAdd.clear();

    lastFrame = currentFrame;
  }
}
