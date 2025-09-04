#include "entity.h"

float sigmoidF(int x){
    return 1/(1+exp(2*x-10));
}
std::string enemyTypeToString(enemy_type type) {
    switch(type) {
        case red_slime: {return "red_slime";break;}
        case blue_slime: {return "blue_slime";break;}
        case king_slime: {return "king_slime";break;}
        default: {return "unknown";break;}
    }
};
std::string towerTypeToString(tower_type type) {
    switch(type) {
        case archer: {return "archer";break;}
        case mage: {return "mage";break;}
        case sniper: {return "sniper";break;}
        default: {return "unknown";break;}
    }
};
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
            stats=std::make_tuple(5,200);
            break;
        }
        default: {
            stats=std::make_tuple(0,0);
            break;
        }
    }
    return stats;
};
//damege, attack_speed, range, damage_area
std::tuple<int,double,int,int> towerTypeToStats(tower_type type) {
    std::tuple<int,double,int,int> stats;
    switch(type) {
        case archer: {
            stats=std::make_tuple(10,0.5,100,1);
            break;
        }
        case mage: {
            stats=std::make_tuple(15,0.7,150,10);
            break;
        }
        case sniper: {
            stats=std::make_tuple(50,3.0,300,1);
            break;
        }
        default: {
            stats=std::make_tuple(0,0.0,0,0);
            break;
        }
    }
    return stats;

};

entity::entity(sf::Texture &textur)
:texture(textur),shape(texture){
};
void entity::draw(sf::RenderTarget &target){
    target.draw(shape);
    //cout<<"WTF?";
};
enemy::enemy(enemy_type typ,sf::Texture textur)
:entity(textur){
    texture=textur;
    shape.setTexture(texture);
    type=typ;
    auto [speed,health]=enemyTypeToStats(type);
    this->speed=speed;
    this->health=health;
    shape.setOrigin(shape.getLocalBounds().getCenter());
};
void enemy::move(double delta_time,vector <sf::Vector2f> path){
    sf::Vector2f position;
    float step=0.0f;
    position=shape.getPosition();
    for(int i=0;i<path.size()-1 && delta_time>0;i++){
        step= speed*delta_time;
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
        //x_increase
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
};
sf::Vector2f enemy::get_pos(){
    return shape.getPosition();
};
bool enemy::damaged(int damage){
    health-=damage;
    if(health<0){
        health=0;
        return true;
    }
    else return false;
};
wave::wave(int wave){
    last_spawn_time=0.0f;
    wave_number=wave;
    enemy_textures.clear();
    enemy_textures.reserve(3);
    enemies.clear();
    enemies.reserve(wave_number/2+wave_number/5+wave_number*2);
    for(int i=0;i<3;i++){
        sf::Texture texture;
        std::string filename = "assets/" + enemyTypeToString(static_cast<enemy_type>(i)) + ".png";
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
        enemy_textures.push_back(texture);
    }
};
void wave::next_wave(){
    wave_number++;
    new_enemies.clear();
    int red_slime_count=wave_number*2;
    int blue_slime_count=wave_number/2;
    int king_slime_count=wave_number/5;
    int enemy_count=red_slime_count+blue_slime_count+king_slime_count;
    new_enemies.reserve(enemy_count);
    for(int i=0;i<red_slime/2;i++){
        enemy new_enemy(red_slime,enemy_textures[red_slime]);
        new_enemies.push_back(new_enemy);
    }
    for(int i=0;i<blue_slime_count;i++){
        enemy new_enemy(blue_slime,enemy_textures[blue_slime]);
        new_enemies.push_back(new_enemy);
    }
    for(int i=0;i<red_slime/2;i++){
        enemy new_enemy(king_slime,enemy_textures[king_slime]);
        new_enemies.push_back(new_enemy);
    }
    for(int i=0;i<king_slime_count;i++){
        enemy new_enemy(king_slime,enemy_textures[king_slime]);
        new_enemies.push_back(new_enemy);
    }
};
vector <enemy> wave::get_enemies() const{
    return enemies;
};
bool wave::spawn_enemies(float current_time){
    last_spawn_time-=current_time;
    if(new_enemies.size()>0){
        if(last_spawn_time<=0.0f){
            enemies.push_back(new_enemies[0]);
            new_enemies.erase(new_enemies.begin());
            last_spawn_time=2.0f/sigmoidF(wave_number);
        }
        return false;
    }
    else return true;
};
tower::tower(tower_type typ,sf::Texture textur,sf::Vector2f position)
:entity(textur){
    this->type=typ;
    texture=textur;
    shape.setTexture(texture);
    auto [damage,attack_speed,range,damage_area]=towerTypeToStats(type);
    this->damage=damage;
    this->attack_speed=attack_speed;
    this->range=range;
    this->damage_area=damage_area;
    last_attack=0.0f;
    shape.setPosition(position);
    //cout<<"Tower "<<towerTypeToString(type)<<" "<<position.x<<" "<<position.y<<endl;
};
float tower::get_lastattack(float deltaT){
    last_attack-=deltaT;
    return last_attack;
};
int tower::get_damage() const{
    return damage;
};
sf::Vector2f tower::get_pos() const{
    return shape.getPosition();
};
int tower::get_range() const{
    return range;
};
double tower::get_attackspeed() const{
    return attack_speed;
};

