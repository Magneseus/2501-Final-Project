#include "GameObject.h"

// TODO: Fix this stupid way of doing things
// (Probably make the GameObject file into an actual proper implementation)

std::vector<GameObject*> GameObject::staticGameObjects;
std::vector<GameObject*> GameObject::staticGameObjectsDel;
std::vector<GameObject*> GameObject::staticGameObjectsRem;

// Some more sp00ky global/static stuff
sf::Vector2i Global::mouseWindowCoords;