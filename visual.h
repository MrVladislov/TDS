#ifndef VISUAL_H
#define VISUAL_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "entity.h"
#pragma once
/**
 * @brief UI Button class for the game interface.
 */
class Button{
private:
    sf::RectangleShape shape;///< Button shape.
    sf::Text text;///< Text displayed on the button.
public:
    /**
     * @brief Constructs a button.
     * @param size Size of the button.
     * @param position Position of the button.
     * @param text Text to display on the button.
     * @param color Button color.
     * @param font Font used for text.
     */
    Button(sf::Vector2f size, sf::Vector2f position, std::string text, sf::Color color,sf::Font &font);
    /**
     * @brief Draws the button on the target.
     * @param target Render target (e.g., window).
     */
    void draw(sf::RenderTarget &target);
    /**
     * @brief Gets the bounding rectangle of the button.
     * @return The bounding rectangle as sf::FloatRect.
     */
    sf::FloatRect get_bound() const;
    /**
     * @brief Marks the button as selected.
     */
    void selected();
    /**
     * @brief Marks the button as unselected.
     */
    void unselected();
};
/**
 * @brief Types of map tiles.
 */
enum class TileType { 
    mountain, 
    grass, 
    swamp,
    stairs,
    castle
};
/**
 * @brief Represents a single tile on the map.
 */
class tile{
private:
    sf::RectangleShape shape;///< Shape of the tile.
    sf::Texture *texture;///< Texture applied to the tile.
public:
    /**
     * @brief Creates a tile with a given type and position.
     * @param type Tile type.
     * @param position Tile position.
     * @param textur Pointer to the texture for the tile.
     */
    tile(int type, sf::Vector2f position,sf::Texture *textur);
    /**
     * @brief Draws the tile on the target.
     */
    void draw(sf::RenderTarget &target);
    /**
     * @brief Gets the bounding rectangle of the tile.
     */
    sf::FloatRect get_bound();
};
/**
 * @brief Represents the game map with tiles.
 */
class map{
private:
    std::vector<std::vector<tile>> tiles;///< 2D grid of tiles.
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
    };///< Template for map generation.
    sf::Vector2f size;///< Size of the map.
    std::vector <sf::Texture> textures;///< Loaded textures.
    bool position_choosen=0;///< Whether a tower position is chosen.
public:
    /**
     * @brief Constructs the map.
     * @param ntextures Number of textures to load.
     */
    map(int ntextures=5);
    /**
     * @brief Loads the map with tiles and textures.
     */
    void loadMap();
    /**
     * @brief Gets the size of the map.
     */
    sf::Vector2f getSize() const;
    /**
     * @brief Draws the map on the target.
     */
    void draw(sf::RenderTarget &target);
    /**
     * @brief Allows placing a tower on the map.
     * @param target The game window.
     * @return Tuple containing position, grid index, and tile type.
     */
    std::tuple<sf::Vector2f,sf::Vector2i,TileType> PlaceTower(sf::Window &target); 
    /**
     * @brief Gets all the tiles.
     */
    std::vector <std::vector<tile>> getTiles();
    /**
     * @brief Gets tile types as integers.
     */
    std::vector<std::vector<int>> get_TilesType() const;
};
/**
 * @brief UI menu for displaying game stats and buttons.
 */
class menu{
private:
    std::vector<Button> buttons;///< Buttons in the menu.
    std::vector<sf::Text> texts;///< Text elements in the menu.
    sf::RectangleShape background;///< Background of the menu.
    sf::Font arialmt;///< Font used for text.
    int selected_button=-1;///< Index of the selected button.
    bool mouse_clicked=false;///< Mouse click state.
public:
    /**
     * @brief Constructs the menu with initial stats.
     * @param balance Player's balance.
     * @param health Player's health.
     * @param waves Current wave number.
     */
    menu(int balance,int health,int waves=0);
    /**
     * @brief Draws the menu on the target.
     * @param target Render target.
     */
    void draw(sf::RenderTarget &target);
    /**
     * @brief Updates displayed stats.
     * @param balance Player's balance.
     * @param health Player's health.
     * @param waves Current wave number.
     */
    void changeStats(int balance,int health,int waves);
    /**
     * @brief Handles tower purchase UI logic.
     * @param target Game window.
     */
    void TowerBuy(sf::Window &target);
    /**
     * @brief Gets the selected tower type.
     * @return Tower type index.
     */
    int getSelectedTower();
};
/**
 * @brief Main Game UI class, responsible for rendering and game loop.
 */
class GameUI{
private:
    sf::RenderWindow window;///< Main game window.
    map mape;///< Game map.
    menu sidemenu;///< Side menu.
    sf::Font arialmt;///< Font used in UI.
    sf::Clock clock;///< Game clock.
    std::vector <tower> towers;///< Placed towers.
    wave waves;///< Current wave of enemies.
    std::vector <sf::Texture> t_textures;///< Tower textures.
    std::vector <std::vector<int>> placed_towers;///< Grid of placed towers.
    float next_wave;///< Time until next wave.
    int numbers_of_tower;///< Number of placed towers.
    int wave_n;///< Current wave number.
public:
    /**
     * @brief Constructs the Game UI.
     * @param width Window width.
     * @param height Window height.
     * @param title Window title.
     * @param balance Player's starting balance.
     * @param health Player's starting health.
     * @param path Path for enemy movement.
     * @param tntexture Number of tower textures.
     * @param map_size Map size in grid coordinates.
     */
    GameUI(int width, int height, std::string title, int balance, int health,std::vector <sf::Vector2f> path,int tntexture=3,
        sf::Vector2i map_size=sf::Vector2i(11,11));
    /**
     * @brief Places static objects (map, menu) on the window.
     */
    void pin_object();
    /**
     * @brief Renders the game UI.
     * @param Balance Player balance reference.
     * @param Health Player health reference.
     * @param deltaT Time delta since last frame.
     */
    void render(int &Balance,int &Health,float deltaT);
    /**
     * @brief Checks if the window is open.
     * @return True if the window is open.
     */
    bool isOpen() const;
    /**
     * @brief Polls window events.
     * @return True if an event occurred.
     */
    bool pollEvent();
    /**
     * @brief Closes the window.
     */
    void close();
    /**
     * @brief Checks if a keyboard button is pressed.
     * @param button_index Button scancode.
     * @return True if pressed, false otherwise.
     */
    bool isButtonPressed(sf::Keyboard::Scancode button_index) const;
    /**
     * @brief Restarts the game clock and returns elapsed time.
     * @return Time elapsed since last restart (last frame).
     */
    float restartClock();
    /**
     * @brief Gets references to enemies and towers.
     * @return Tuple of vectors (enemies, towers).
     */
    tuple <vector<enemy>&,vector<tower>&> get_entities();
};
#endif 