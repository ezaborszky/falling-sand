#include "Entity.hpp"

Entity::Entity(int id, int x, int y) : m_id(id), m_x(x), m_y(y) {}

void Entity::destroy() { isActive = false; }
