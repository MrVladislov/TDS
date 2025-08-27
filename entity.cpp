#include "entity.h"

class Entity {
public:
    sf::vector2f position
};
class enemy : public Entity{

};
class Tower : public Entity{
private:
    int damage;
    float range;
    float attackSpeed;
};