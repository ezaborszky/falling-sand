#include "Systems.hpp"

void renderObjects(sf::RenderWindow &window, EntityVector &entVec) {
  window.clear();
  for (auto e : entVec) {
    if (e->compShape) {
      window.draw(e->compShape->circleShape);
    }
  }
  window.display();
}
