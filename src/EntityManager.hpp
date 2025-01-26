#pragma once
#include "Entity.hpp"
#include <map>
#include <memory>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;

class EntityManager {
public:
  EntityVector m_entities;
  EntityVector m_entitiesToAdd;

  EntityManager();
  std::shared_ptr<Entity> addEntity(int id);
  void Update();
  void removeDead(EntityVector &vec);
};
