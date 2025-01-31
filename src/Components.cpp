#include "Components.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <utility>

Shape::Shape(sf::Vector2f size) : circleShape(size) {};

TileMap::TileMap() {};

void TileMap::updateCellsList(int x, int y) {
  m_activeCells.push_back(std::pair<int, int>(x, y));
};

bool TileMap::checkGridCell(int x, int y, TileMap::cellType type) {
  return (grid[x][y] == type);
};
void TileMap::setGridCell(int x, int y, TileMap::cellType type) {
  grid[x][y] = type;
};
