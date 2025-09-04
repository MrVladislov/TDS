#ifndef VISUAL_H
#define VISUAL_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "entity.h"

class Button{
private:
    sf::RectangleShape shape;
    sf::Text text;
public:
    Button(sf::Vector2f size, sf::Vector2f position, std::string text, sf::Color color,sf::Font &font);
    void draw(sf::RenderTarget &target);
    sf::FloatRect get_bound() const;
    void selected();
    void unselected();
};
enum class TileType { 
    mountain, 
    grass, 
    swamp,
    stairs,
    castle
};
class tile{
private:
    sf::RectangleShape shape;
    sf::Texture *texture;
public:
    tile(int type, sf::Vector2f position,sf::Texture *textur);
    void draw(sf::RenderTarget &target);
    sf::FloatRect get_bound();
};
class map{
private:
    std::vector<std::vector<tile>> tiles;
    std::vector<std::vector<int>> map_template{
        {0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,3,3,1,1,1,2,0},
        {0,0,0,0,0,0,0,0,0,1,0},
        {0,1,1,1,2,1,1,1,0,1,0},
        {0,1,0,0,0,0,0,1,0,1,0},
        {0,1,0,3,3,4,0,1,0,2,0},
        {0,1,0,2,0,0,0,2,0,1,0},
        {0,1,0,1,1,1,1,1,0,1,0},
        {0,1,0,0,0,0,0,0,0,1,0},
        {0,1,1,3,3,1,1,1,1,3,0},
        {0,0,0,0,0,0,0,0,0,0,0}
    };
    //std::vector<std::vector<int>> map_template{{0,0},{1,1},{2,2},{3,3},{4,4}};
    sf::Vector2f size;
    std::vector <sf::Texture> textures;
    bool position_choosen=0;
public:
    map(int ntextures=5);
    void loadMap();
    sf::Vector2f getSize() const;
    void draw(sf::RenderTarget &target);
    std::tuple<sf::Vector2f,sf::Vector2i,TileType> PlaceTower(sf::Window &target);
};
class menu{
private:
    std::vector<Button> buttons;
    std::vector<sf::Text> texts;
    sf::RectangleShape background;
    sf::Font arialmt;
    int selected_button=-1;
    bool mouse_clicked=false;
public:
    menu(int balance,int health);
    void draw(sf::RenderTarget &target);
    void changeStats(int balance,int health);
    void TowerBuy(sf::Window &target);
    int getSelectedTower();
};
class GameUI{
private:
    sf::RenderWindow window;
    map mape;
    menu sidemenu;
    sf::Font arialmt;
    sf::Clock clock;
    std::vector <tower> towers;
    wave waves;
    std::vector <sf::Texture> t_textures;
    std::vector <std::vector<int>> placed_towers;
public:
    GameUI(int width, int height, std::string title, int balance, int health,int tntexture=3,sf::Vector2i map_size=sf::Vector2i(11,11));
    void pin_object();
    void render(int Balance,int Health);
    bool isOpen() const;
    bool pollEvent();
    void close();
    bool isButtonPressed(sf::Keyboard::Scancode button_index) const;
    float restartClock();
};
#endif 