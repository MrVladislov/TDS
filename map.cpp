#include "map.h"
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