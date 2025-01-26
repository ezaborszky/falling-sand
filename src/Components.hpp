#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Shape {
public:
  sf::CircleShape circleShape;
  Shape(int radius, int points);
};

class TileMap {
public:
  enum cellType { EMPTY, SAND };
  static constexpr int WIDTH = 100;
  static constexpr int HEIGHT = 100;
  cellType grid[WIDTH][HEIGHT] = {cellType::EMPTY};
  TileMap();
};
