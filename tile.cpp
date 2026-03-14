#include "tile.h"



std::string tileTypeToString(TileType type) {
    switch(type) {
        case TileType::mountain: {return "mountain";break;}
        case TileType::grass:    {return "grass";break;}
        case TileType::swamp:    {return "swamp";break;}
        case TileType::stairs:   {return "stairs";break;}
        case TileType::castle:   {return "castle";break;}
        default:                 {return "unknown";break;}
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
sf::FloatRect tile::get_bound(){
    return shape.getGlobalBounds();
};