#include "visual.h"
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
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(position + sf::Vector2f(1.0f, 5.0f));
};
void Button::draw(sf::RenderTarget &target) {
    target.draw(shape);
    target.draw(text);
}

GameUI::GameUI(int width, int height, string title, int balance, int health) 
: mape(), sidemenu(balance, health){
    if (!arialmt.openFromFile("arialmt.ttf")) {
        throw std::runtime_error("Failed to load font: arialmt.ttf");
    }
    window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    window.setFramerateLimit(60);
    window.clear(sf::Color::Red);
    pin_object();
    window.display();
};
void GameUI::pin_object(){
    mape.draw(window);
    sidemenu.draw(window);
}
void GameUI::render(int balance, int health){
    if (!window.isOpen()) return;
    window.clear(sf::Color::Black);
    mape.draw(window);
    sidemenu.changeStats(balance, health);
    sidemenu.draw(window);
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
            // sf::RectangleShape debugRect(sf::Vector2f(64,64));
            // debugRect.setPosition({j*64.0f+10.0f, i*64.0f+10.0f});
            // debugRect.setFillColor(sf::Color(0,255,0,100));
            // target.draw(debugRect);
        }
    }
};


tile::tile(int type,sf::Vector2f position,sf::Texture *textur)
{

    std::string filename = "assets/" + tileTypeToString(static_cast<TileType>(type)) + ".png";
    texture = textur;
    shape.setSize(sf::Vector2f(64.0f,64.0f));
    shape.setTexture(texture, true);
    shape.setPosition(position);   
};
void tile::draw(sf::RenderTarget &target){
    target.draw(shape); 
};


menu::menu(int balance,int health){
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
    Button button(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 60.0f), "Archer tower (100)", sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button);
    Button button2(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 100.0f), "Mage tower (200)", sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button2);
    Button button3(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 140.0f), "Sniper tower (300)", sf::Color(160, 160, 160),arialmt);
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
void menu::changeStats(int balance, int health){
    this->texts[0].setString("Balance:"+to_string(balance));
    this->texts[1].setString("Health:"+to_string(health));
};
