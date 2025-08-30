#ifndef VISUAL_H
#define VISUAL_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Button{
private:
    sf::RectangleShape shape;
    sf::Text text;
public:
    Button(sf::Vector2f size, sf::Vector2f position, std::string text, sf::Color color,sf::Font &font);
    void draw(sf::RenderTarget &target);
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
public:
    map(int ntextures=5);
    void loadMap();
    sf::Vector2f getSize() const;
    void draw(sf::RenderTarget &target);
};
class menu{
private:
    std::vector<Button> buttons;
    std::vector<sf::Text> texts;
    sf::RectangleShape background;
    sf::Font arialmt;
public:
    menu(int balance,int health);
    void draw(sf::RenderTarget &target);
    void changeStats(int balance,int health);
};
class GameUI{
private:
    sf::RenderWindow window;
    map mape;
    menu sidemenu;
    sf::Font arialmt;
public:
    GameUI(int width, int height, std::string title, int balance, int health);
    void pin_object();
    void render(int Balance,int Health);
    bool isOpen() const;
    bool pollEvent();
    void close();
};
#endif 