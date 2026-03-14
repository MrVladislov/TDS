#include "wave.h"

float sigmoidF(int x){
    return 0.8/(1+exp(x/2-10))+0.2;
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