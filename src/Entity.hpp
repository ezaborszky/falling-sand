#pragma once
#include "Components.hpp"
#include <memory>

class Entity {

public:
  Entity(int id, int x, int y);
  std::shared_ptr<Shape> compShape;
  void destroy();
  int m_id, m_x, m_y;
  bool isActive = true;
};
