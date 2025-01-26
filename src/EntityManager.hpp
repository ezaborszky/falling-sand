#pragma once
#include "Entity.hpp"
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;

template <class T1, class T2> struct hash_pair {
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    return h1 ^ h2;
  }
};

using EntityMap =
    std::unordered_map<std::pair<int, int>, std::shared_ptr<Entity>,
                       hash_pair<int, int>>;

class EntityManager {
public:
  EntityMap entMap;
  EntityManager();
  std::shared_ptr<Entity> addEntity(int id, int x, int y);
  void Update();
  void removeDead(EntityVector &vec);
};
