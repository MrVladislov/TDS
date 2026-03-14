#include "entity.h"
entity::entity(sf::Texture &textur)
:shape(textur){};

void entity::draw(sf::RenderTarget &target){
    target.draw(shape);
    //cout<<"WTF?";
    //cout<<"Yes "<<shape.getPosition().x<<" "<<shape.getPosition().y<<" "<<shape.getTexture().getSize().x<<" "<<shape.getTexture().getSize().x<<endl;
};
sf::Vector2f entity::get_pos() const{
    return shape.getPosition();
};