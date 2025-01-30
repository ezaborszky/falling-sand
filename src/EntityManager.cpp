#include "EntityManager.hpp"
#include <memory>
#include <unordered_map>

EntityManager::EntityManager() {};

void EntityManager::removeDead() {
  for (auto it = entMap.begin(); it != entMap.end();) {
    if (!it->second->isActive) {
      it = entMap.erase(it);
    } else {
      ++it;
    }
  }
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
