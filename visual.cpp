#include "visual.h"
#include <iostream>
using namespace std;




GameUI::GameUI(int width, int height, string title, int balance, int health,std::vector <sf::Vector2f> path,int tntexture,
    sf::Vector2i map_size) 
: mape(), sidemenu(balance, health),waves(path){
    if (!arialmt.openFromFile("arialmt.ttf")) {
        throw std::runtime_error("Failed to load font: arialmt.ttf");
    }
    window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    window.setFramerateLimit(60);
    window.clear(sf::Color::Red);
    pin_object();
    window.display();
    t_textures.clear();
    t_textures.resize(tntexture);
    for(int i=0;i<tntexture;i++){
        std::string t_filename = "assets/" + towerTypeToString(static_cast<tower_type>(i)) + ".png";
        if(!t_textures[i].loadFromFile(t_filename)){
            throw std::runtime_error("Failed to load tower textures: "+t_filename);
        }
    }
    //placed_towers.clear();
    placed_towers.resize(map_size.x);
    for(int i=0;i<map_size.x;i++){
        //placed_towers[i].clear();
        placed_towers[i].resize(map_size.y);
        for(int j=0;j<map_size.y;j++){
            placed_towers[i][j]=-1;
        }
    }
    wave_n=0;
    numbers_of_tower=0;
    next_wave=0.f;
};
void GameUI::pin_object(){
    mape.draw(window);
    sidemenu.draw(window);
}
void GameUI::render(int &balance, int &health,float deltaT){
    if (!window.isOpen()) return;
    window.clear(sf::Color::Black);
    sidemenu.TowerBuy(window);
    auto[tower_pos,tile_pos,tile_typ]=mape.PlaceTower(window);
    int tower_typ=sidemenu.getSelectedTower();
    int tower_cost=getTowerCost(tower_typ);
    if(tower_pos!=sf::Vector2f(-1.0f,-1.0f) && placed_towers[tile_pos.x][tile_pos.y]==-1 
        && tile_typ==TileType::mountain && tower_typ!=-1 && balance>=tower_cost){
        tower new_tower(static_cast<tower_type>(tower_typ),t_textures[tower_typ],tower_pos);
        placed_towers[tile_pos.x][tile_pos.y]=tower_typ;
        balance-=tower_cost;
        towers.push_back(new_tower);
        numbers_of_tower++;
        //cout<<"Slurp at"<<tower_pos.x<<" "<<tower_pos.y<<endl;
    }
    mape.draw(window);
    if(wave_n!=waves.getWave()){
        throw("Oh! Something wrong with waves");
    }
    std::vector <enemy> &enemies=waves.get_enemies();
    std::vector <std::vector<tile>> tiles=mape.getTiles();
    std::vector <std::vector<int>> tilesType=mape.get_TilesType();
    for(int k=0;k<enemies.size();k++)
    {    
        for(int i=0;i<tiles.size();i++){
            for(int j=0;j<tiles[i].size();j++){
                if((tiles[i][j].get_bound()).contains(enemies[k].get_pos())){
                    switch (static_cast<TileType> (tilesType[i][j]))
                    {
                        case TileType::grass:   {enemies[k].Buff(1);break;}
                        case TileType::swamp:   {enemies[k].Buff(0.8);break;}
                        case TileType::stairs:  {enemies[k].Buff(1.2);break;}
                        case TileType::castle:  {enemies[k].damaged(1000000);health--;break;}
                    }
                }
            }
        }
    }

    sidemenu.changeStats(balance, health,wave_n);
    sidemenu.draw(window);
    for(auto &tower:towers){
        tower.draw(window);
    }
    if(numbers_of_tower>0){
        if(next_wave<=0.f)
        {
            if(wave_n!=0)balance+=10*(wave_n/5+1);
            wave_n++;
            waves.next_wave();
            next_wave+=waves.getWaveLong()+30.f*sigmoidF(wave_n);
        }
        else next_wave-=deltaT;
    }
    if(waves.spawn_enemies(deltaT)){
        //cout<<"Pip"<<endl;
    }
    waves.draw(window,deltaT);
    //cout<<"Number of towers "<<towers.size()<<endl;
    window.display();
    
};
bool GameUI::isOpen() const{
    return window.isOpen();
};
void GameUI::close(){
    window.close();
};
bool GameUI::pollEvent(){
    auto event = window.pollEvent();
    return event && event->is<sf::Event::Closed>();
};
bool GameUI::isButtonPressed(sf::Keyboard::Scancode button_index) const{
    if (sf::Keyboard::isKeyPressed(button_index)) {
        return true;
    }
    else{
        return false;
    }
};
float GameUI::restartClock(){
    sf::Time time = clock.restart();
    return time.asSeconds();
};
tuple <vector<enemy>&,vector<tower>&> GameUI::get_entities(){
    return std::tie(waves.get_enemies(), towers);
};
sf::RenderWindow &GameUI::get_target(){
    return window;
};

