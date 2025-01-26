#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Shape {
public:
  sf::CircleShape circleShape;
  Shape(int radius, int points);
};
