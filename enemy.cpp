#include "enemy.h"

std::string enemyTypeToString(enemy_type type) {
    switch(type) {
        case red_slime: {return "red_slime";break;}
        case blue_slime: {return "blue_slime";break;}
        case king_slime: {return "king_slime";break;}
        default: {return "unknown";break;}
    }
};
//speed, health
std::tuple<int,int> enemyTypeToStats(enemy_type type) {
    std::tuple<int,int> stats;
    switch(type) {
        case red_slime: {
            stats=std::make_tuple(10,50);
            break;
        }
        case blue_slime: {
            stats=std::make_tuple(20,30);
            break;
        }
        case king_slime: {
            stats=std::make_tuple(5,300);
            break;
        }
        default: {
            stats=std::make_tuple(0,0);
            break;
        }
    }
    return stats;
};
int getEnemyCost(int typ){
    constexpr int EnemyPrices[] = { 10, 10, 50 };
    return EnemyPrices[typ];
};
int getEnemyHealth(enemy_type typ){
    constexpr int EnemyHealth[] = { 50, 30, 300 };
    return EnemyHealth[typ];
};
bool enemy::draw(sf::RenderTarget &target){
    if(health<=0)return true;
    else{
        entity::draw(target);
        target.draw(health_bar);
        return false;
    }
};
enemy::enemy(enemy_type typ,sf::Texture &textur)
:entity(textur){
    shape.setTexture(textur);
    type=typ;
    auto [speed,health]=enemyTypeToStats(type);
    this->speed=speed;
    this->health=health;
    shape.setOrigin(shape.getLocalBounds().getCenter());
    health_bar.setFillColor(sf::Color::Red);
    health_bar.setSize({40.f,10.f});
    health_bar.setOutlineColor(sf::Color::Black);
    health_bar.setOutlineThickness(1.f);
    health_bar.setOrigin({20.f,5.f});
    buff=1;
};
void enemy::move(float delta_time,vector <sf::Vector2f> path){
    sf::Vector2f position;
    float step=0.0f;
    position=shape.getPosition();
    for(int i=0;i<path.size()-1 && delta_time>0;i++){
        step= speed*delta_time*buff;
        //x_decrease
        if(path[i].x-path[i+1].x>1){
            if(abs(position.y-path[i].y)<0.0001){
                if(position.x-step<path[i+1].x){
                    delta_time-=(position.x-path[i+1].x)/speed;
                    position.x=path[i+1].x;
                }
                else{
                    position.x-=step;
                    delta_time=0;
                }
            }
        }
        //x_increase
        else if(path[i].x-path[i+1].x<-1){
            if(abs(position.y-path[i].y)<0.0001){
                if(position.x+step>path[i+1].x){
                    delta_time-=(path[i+1].x-position.x)/speed;
                    position.x=path[i+1].x;
                }
                else{
                    position.x+=step;
                    delta_time=0;
                }
            }
        }
        //y_decrease
        else if(path[i].y-path[i+1].y>1){
            if(abs(position.x-path[i].x)<0.0001){
                if(position.y-step<path[i+1].y){
                    delta_time-=(position.y-path[i+1].y)/speed;
                    position.y=path[i+1].y;
                }
                else{
                    position.y-=step;
                    delta_time=0;
                }
            }
        }
        //y_increase
        else if(path[i].y-path[i+1].y<-1){
            if(abs(position.x-path[i].x)<0.0001){
                if(position.y+step>path[i+1].y){
                    delta_time-=(path[i+1].y-position.y)/speed;
                    position.y=path[i+1].y;
                }
                else{
                    position.y+=step;
                    delta_time=0;
                }
            }
        }
    }
    shape.setPosition(position);
    health_bar.setSize({40.f*(float(health)/float(getEnemyHealth(type))),10.f});
    health_bar.setPosition({position.x,position.y-40.f});
};
bool enemy::damaged(int damage){
    health-=damage;
    if(health<=0){
        return true;
    }
    else return false;
};
void enemy::set_pos(sf::Vector2f spawn_point){
    shape.setPosition(spawn_point);
};
enemy_type enemy::get_type() const{
    return type;
};
void enemy::Buff(double buff){
    this->buff=buff;
};