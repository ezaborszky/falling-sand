#pragma once
#include "Components.hpp"
#include "EntityManager.hpp"
#include <memory>

class Entity {
  friend class EntityManager;
  Entity();

public:
  std::shared_ptr<Shape> compShape;
  void destroy();
};
