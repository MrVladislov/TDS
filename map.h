#ifndef MAP_H
#define MAP_H
#include <vector>
#include "tile.h"


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

#endif