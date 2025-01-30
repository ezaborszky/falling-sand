#pragma once
#include "Components.hpp"
#include "EntityManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void renderObjects(sf::RenderWindow &window, EntityMap &entMap);
void drawMap(int height, int width, TileMap &tileMap, EntityMap &entMap,
             EntityManager &manager);
void setCell(sf::RenderWindow &window, sf::Event &event, TileMap &TileMap);
void moveCells(EntityMap &entMap, TileMap &tileMap, unsigned int &currentFrame,
               unsigned int &lastFrame);
