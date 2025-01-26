#pragma once
#include "Components.hpp"
#include <memory>

class Entity {

public:
  Entity(int id);
  std::shared_ptr<Shape> compShape;
  void destroy();
  int id;
  bool isActive = true;
};
