#ifndef VISUAL_H
#define VISUAL_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "entity.h"
#include "enemy.h"
#include "menu.h"
#include "map.h"
#include "tower.h"
#include "wave.h"


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
    sf::RenderWindow &get_target();
};
#endif 