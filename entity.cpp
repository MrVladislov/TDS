#include "entity.h"

float sigmoidF(int x){
    return 0.8/(1+exp(x/2-10))+0.2;
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
double getTowerAttackSpeed(tower_type typ){
    constexpr double TowerAS[] = { 1.3, 3, 10 };
    return TowerAS[typ];
};
//damege, attack_speed, range, damage_area,cost
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

entity::entity(sf::Texture &textur)
:shape(textur){};

void entity::draw(sf::RenderTarget &target){
    target.draw(shape);
    //cout<<"WTF?";
    //cout<<"Yes "<<shape.getPosition().x<<" "<<shape.getPosition().y<<" "<<shape.getTexture().getSize().x<<" "<<shape.getTexture().getSize().x<<endl;
};
bool enemy::draw(sf::RenderTarget &target){
    if(health<=0)return true;
    else{
        entity::draw(target);
        target.draw(health_bar);
        return false;
    }
}
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
wave::wave(std::vector <sf::Vector2f> path,int wave){
    last_spawn_time=0.0f;
    wave_number=wave;
    this->path=path;
    enemy_textures.clear();
    enemy_textures.reserve(3);
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
    for(int i=0;i<red_slime_count/2;i++){
        enemy new_enemy(red_slime,enemy_textures[red_slime]);
        new_enemies.push_back(new_enemy);
    }
    for(int i=0;i<blue_slime_count;i++){
        enemy new_enemy(blue_slime,enemy_textures[blue_slime]);
        new_enemies.push_back(new_enemy);
    }
    for(int i=0;i<red_slime_count/2;i++){
        enemy new_enemy(red_slime,enemy_textures[red_slime]);
        new_enemies.push_back(new_enemy);
    }
    for(int i=0;i<king_slime_count;i++){
        enemy new_enemy(king_slime,enemy_textures[king_slime]);
        new_enemies.push_back(new_enemy);
    }
};
vector <enemy> &wave::get_enemies(){
    return enemies;
};
bool wave::spawn_enemies(float current_time){
    if(new_enemies.size()>0){
        last_spawn_time-=current_time;
        if(last_spawn_time<=0.0f){
            new_enemies[0].set_pos(path[0]);
            enemies.push_back(new_enemies[0]);
            new_enemies.erase(new_enemies.begin());
            last_spawn_time+=5.0f*sigmoidF(wave_number);
            //cout<<"Spawned"<<endl;
        }
        return false;
    }
    else return true;
};
float wave::getWaveLong() const{
    return (wave_number/2+wave_number/5+wave_number*2)*5.0f*sigmoidF(wave_number);
};
int wave::getWave() const{
    return wave_number;
};
void wave::draw(sf::RenderTarget &target,float deltaT){
    for(int i=0;i<enemies.size();){
        enemies[i].move(deltaT,path);
        if(enemies[i].draw(target)){
            enemies.erase(enemies.begin()+i);
        }
        else ++i;
    }
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
void enemy::set_pos(sf::Vector2f spawn_point){
    shape.setPosition(spawn_point);
};
sf::Vector2f entity::get_pos() const{
    return shape.getPosition();
};

enemy_type enemy::get_type() const{
    return type;
};
tower_type tower::get_type() const{
    return type;
};
int tower::get_damagearea() const{
    return damage_area;
};
void enemy::Buff(double buff){
    this->buff=buff;
};