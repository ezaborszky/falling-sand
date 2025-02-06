#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <utility>
#include <vector>

class Shape {
public:
  sf::RectangleShape circleShape;
  Shape(sf::Vector2f size);
};

class TileMap {
public:
  enum cellType { EMPTY, SAND, WATER, ROCK };
  static constexpr int WIDTH = 200;
  static constexpr int HEIGHT = 200;
  cellType grid[WIDTH][HEIGHT] = {cellType::EMPTY};
  bool hasMoved[WIDTH][HEIGHT] = {false};
  TileMap();
  std::vector<std::pair<int, int>> m_cellsToAdd;
  std::vector<std::pair<int, int>> m_activeCells;
  void updateCellsList(int x, int y);
  bool checkGridCell(int x, int y, TileMap::cellType type);
  void setGridCell(int x, int y, TileMap::cellType type);
};
