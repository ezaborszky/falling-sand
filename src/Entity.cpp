#include "Entity.hpp"

Entity::Entity(int xid) : id(xid) {}

void Entity::destroy() { isActive = false; }
