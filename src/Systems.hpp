#pragma once
#include "Components.hpp"
#include "EntityManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void renderObjects(sf::RenderWindow &window, EntityMap &entMap);
void drawMap(int height, int width, TileMap::cellType (&grid)[500][500],
             EntityMap &entMap, EntityManager &manager, int &frame);
void setCell(sf::RenderWindow &window, sf::Event &event,
             TileMap::cellType (&grid)[500][500]);
