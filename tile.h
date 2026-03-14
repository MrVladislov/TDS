#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

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
std::string tileTypeToString(TileType type);
#endif