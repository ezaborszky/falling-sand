#pragma once
#include "Entity.hpp"
#include <map>
#include <memory>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;

class EntityManager {
  EntityVector m_entities;
  EntityVector m_entitiesToAdd;

public:
  EntityManager();
};
