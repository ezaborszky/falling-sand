#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Shape {
public:
  sf::RectangleShape circleShape;
  Shape(sf::Vector2f size);
};

class TileMap {
public:
  enum cellType { EMPTY, SAND };
  static constexpr int WIDTH = 500;
  static constexpr int HEIGHT = 500;
  cellType grid[WIDTH][HEIGHT] = {cellType::EMPTY};
  TileMap();
};
