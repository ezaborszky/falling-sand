#include "EntityManager.hpp"
#include <memory>

EntityManager::EntityManager() {};

void EntityManager::removeDead(EntityVector &vec) {
  auto del = std::remove_if(
      vec.begin(), vec.end(),
      [](const std::shared_ptr<Entity> &entity) { return !entity->isActive; });
  vec.erase(del, vec.end());
}

// void EntityManager::Update() {
//   for (auto e : m_entitiesToAdd) {
//     m_entities.push_back(e);
//   }
//
//   removeDead(m_entities);
//   m_entitiesToAdd.clear();
// }
//
std::shared_ptr<Entity> EntityManager::addEntity(int id, int x, int y) {
  auto e = std::make_shared<Entity>(id, x, y);
  entMap[{x, y}] = e;
  return e;
}
