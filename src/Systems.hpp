#pragma once
#include "Components.hpp"
#include "EntityManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

void renderObjects(sf::RenderWindow &window, EntityMap &entMap);
void drawMap(int height, int width, TileMap::cellType (&grid)[100][100],
             EntityMap &entMap, EntityManager &manager);
