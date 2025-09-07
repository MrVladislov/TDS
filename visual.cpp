#include "visual.h"
#include "entity.h"
#include <iostream>
using namespace std;

std::string tileTypeToString(TileType type) {
    switch(type) {
        case TileType::mountain: {return "mountain";break;}
        case TileType::grass:    {return "grass";break;}
        case TileType::swamp:    {return "swamp";break;}
        case TileType::stairs:   {return "stairs";break;}
        case TileType::castle:   {return "castle";break;}
        default:                 {return "unknown";break;}
    }
}
Button::Button(sf::Vector2f size, sf::Vector2f position, string text, sf::Color color, sf::Font &font) 
:text(font, text, 12)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color(255,0,0));
    shape.setOutlineThickness(0.0f);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(position + sf::Vector2f(1.0f, 5.0f));
};
void Button::draw(sf::RenderTarget &target) {
    target.draw(shape);
    target.draw(text);
}

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
}
float GameUI::restartClock(){
    sf::Time time = clock.restart();
    return time.asSeconds();
}
tuple <vector<enemy>&,vector<tower>&> GameUI::get_entities(){
    return std::tie(waves.get_enemies(), towers);
}
map::map(int ntextures){
    size = sf::Vector2f(704.0f, 704.0f);
    tiles.resize(map_template.size());
    for (size_t i = 0; i < map_template.size(); i++) {
        tiles[i].reserve(map_template[i].size());
    }
    textures.resize(ntextures);
    for(int i=0; i<ntextures; i++){
        std::string filename = "assets/" + tileTypeToString(static_cast<TileType>(i)) + ".png";
        if (!textures[i].loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
    }
    loadMap();
};
void map::loadMap(){
    for(int i=0; i<map_template.size(); i++){
        tiles[i].clear();
        for(int j=0; j<map_template[i].size(); j++){
            tiles[i].push_back(tile(map_template[i][j],sf::Vector2f(j*64.0f+10.0f,i*64.0f+10.0f), &textures[map_template[i][j]]));
        }
    }
};
sf::Vector2f map::getSize() const{
    return size;
};
void map::draw(sf::RenderTarget &target){
    for(int i=0; i<tiles.size(); i++){
        for(int j=0; j<tiles[i].size(); j++){
            tiles[i][j].draw(target);
        }
    }
};


tile::tile(int type,sf::Vector2f position,sf::Texture *textur)
{
    texture = textur;
    shape.setSize(sf::Vector2f(64.0f,64.0f));
    shape.setTexture(texture, true);
    shape.setPosition(position);   
};
void tile::draw(sf::RenderTarget &target){
    target.draw(shape); 
};


menu::menu(int balance,int health,int waves){
    texts.clear();
    arialmt = sf::Font("arialmt.ttf");
    background.setSize(sf::Vector2f(200.0f, 720.0f));
    background.setPosition(sf::Vector2f(1080.0f, 0.0f));
    background.setFillColor(sf::Color(96, 96, 96));
    sf::Text text(arialmt, "Balance:" + std::to_string(balance), 12);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(1100.0f, 10.0f));
    texts.push_back(text);
    sf::Text text2(arialmt, "Health:" + std::to_string(health), 12);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(1100.0f, 30.0f));
    texts.push_back(text2);
    sf::Text text3(arialmt, "Wave:" + std::to_string(waves), 12);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(sf::Vector2f(1100.0f, 50.0f));
    texts.push_back(text3);
    Button button(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 100.0f), "Archer tower ("+to_string(getTowerCost(0))+")",
     sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button);
    Button button2(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 140.0f), "Mage tower ("+to_string(getTowerCost(1))+")",
     sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button2);
    Button button3(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 180.0f), "Sniper tower ("+to_string(getTowerCost(2))+")",
     sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button3);
};
void menu::draw(sf::RenderTarget &target){
    target.draw(background);
    for(auto &text : texts){
        target.draw(text);
    }
    for(auto &button : buttons){
        button.draw(target);
    }
};
void menu::changeStats(int balance, int health,int waves){
    this->texts[0].setString("Balance:"+to_string(balance));
    this->texts[1].setString("Health:"+to_string(health));
    this->texts[2].setString("Waves:"+to_string(waves));
};
sf::FloatRect Button::get_bound() const { return shape.getGlobalBounds(); }
void menu::TowerBuy(sf::Window &target){
    for(int i=0;i<buttons.size();i++){
    sf::FloatRect rect=buttons[i].get_bound();
    sf::Vector2f mouse_pos=sf::Vector2f(sf::Mouse::getPosition(target));
    //cout<<"mouse "<<mouse_pos.x<<" "<<mouse_pos.y<<endl<<"but "<<rect.position.x<<" "<<rect.position.y<<endl;
        if(rect.contains(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouse_clicked){
            //cout<<"Button "<<i<<" "<<selected_button<<endl;
            mouse_clicked=1;
            if(selected_button!=i){
                selected_button=i;
                buttons[i].selected();
                break;
            }
            else{
                selected_button=-1;
                buttons[i].unselected();
                break;
            }
        }
    }
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))mouse_clicked=0;
    for(int i=0;i<buttons.size();i++){
        if(i!=selected_button || selected_button==-1)
            buttons[i].unselected();
    }
}
void Button::selected(){
    shape.setOutlineThickness(2.0f);
}
void Button::unselected(){
    shape.setOutlineThickness(0.0f);
}
int menu::getSelectedTower(){
    return selected_button;
}
sf::FloatRect tile::get_bound(){
    return shape.getGlobalBounds();
}
std::tuple<sf::Vector2f,sf::Vector2i,TileType> map::PlaceTower(sf::Window &target){
    if(!position_choosen){
        for(int i=0;i<tiles.size();i++){
            for(int j=0;j<tiles[i].size();j++){
                sf::FloatRect tile_bound=tiles[i][j].get_bound();
                sf::Vector2f mouse_pos=sf::Vector2f(sf::Mouse::getPosition(target));
                if(tile_bound.contains(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    position_choosen=1;
                    //cout<<"Suck "<<tile_bound.getCenter().x<<" "<<tile_bound.getCenter().y<<endl;
                    return std::make_tuple(tile_bound.getCenter(),sf::Vector2i(i,j),static_cast<TileType>(map_template[i][j]));
                }
            }
        }
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))position_choosen=0;
    return std::make_tuple(sf::Vector2f(-1.0f,-1.0f),sf::Vector2i(-1,-1),static_cast<TileType>(-1));
}
std::vector <std::vector<tile>> map::getTiles(){
    return tiles;
}
std::vector<std::vector<int>> map::get_TilesType() const{
    return map_template;
}

