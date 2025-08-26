#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class Entity {
public:
    sf::vector2f position
};
class enemy : public Entity{};
class Tower : public Entity{};

#endif