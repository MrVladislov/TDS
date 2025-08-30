#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class Entity {
public:
    sf::Vector2f position;
};
class enemy : public Entity{

};
class Tower : public Entity{
private:
    int damage;
    float range;
    float attackSpeed;
};

#endif