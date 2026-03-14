#include "tower.h"

std::string towerTypeToString(tower_type type) {
    switch(type) {
        case archer: {return "archer";break;}
        case mage: {return "mage";break;}
        case sniper: {return "sniper";break;}
        default: {return "unknown";break;}
    }
};
double getTowerAttackSpeed(tower_type typ){
    constexpr double TowerAS[] = { 1.3, 3, 10 };
    return TowerAS[typ];
};
//damage, attack_speed, range, damage_area,cost
std::tuple<int,double,int,int,int> towerTypeToStats(tower_type type) {
    std::tuple<int,double,int,int,int> stats;
    switch(type) {
        case archer: {
            stats=std::make_tuple(10,1.3,125,1,100);
            break;
        }
        case mage: {
            stats=std::make_tuple(5,3,150,64,200);
            break;
        }
        case sniper: {
            stats=std::make_tuple(25,10.0,300,1,300);
            break;
        }
        default: {
            stats=std::make_tuple(0,0.0,0,0,0);
            break;
        }
    }
    return stats;

};
tower::tower(tower_type typ,sf::Texture &textur,sf::Vector2f position)
:entity(textur){
    this->type=typ;
    shape.setTexture(textur);
    auto [damage,attack_speed,range,damage_area,cost]=towerTypeToStats(type);
    this->damage=damage;
    this->attack_speed=attack_speed;
    this->range=range;
    this->damage_area=damage_area;
    this->cost=cost;
    last_attack=0.0f;
    shape.setOrigin(sf::Vector2f(16.f,16.f));
    shape.setPosition(position);
    //cout<<"Tower "<<towerTypeToString(type)<<" "<<position.x<<" "<<position.y<<endl;
};
float tower::get_lastattack(float deltaT){
    last_attack-=deltaT;
    return last_attack;
};
void tower::set_lastattack(float next_attack){
    last_attack+=next_attack;
};
int tower::get_damage() const{
    return damage;
};
int tower::get_range() const{
    return range;
};
double tower::get_attackspeed() const{
    return attack_speed;
};
int tower::getCost() const{
    return cost;
};
int getTowerCost(int typ){
    constexpr int towerPrices[] = { 200, 500, 1000 };
    return towerPrices[typ];
};
tower_type tower::get_type() const{
    return type;
};
int tower::get_damagearea() const{
    return damage_area;
};