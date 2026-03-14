#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
//#include "visual.h"
using namespace std;
#pragma once

/**
 * @brief Base class for all entities (towers and enemies).
 */
class entity{
protected:
	sf::Sprite shape;///< Sprite representing the entity.
	sf::Vector2f position;///< Current position of the entity.
public:
    /**
     * @brief Constructor for entity.
     * @param textur Reference to texture to apply to the entity.
     */
    entity(sf::Texture &textur);
    /**
     * @brief Draws the entity on the given target.
     * @param target Render target (e.g., window).
     */
	void draw(sf::RenderTarget &target);
    /**
     * @brief Gets the current position of the entity.
     * @return Position as sf::Vector2f.
     */
    sf::Vector2f get_pos() const;
};

#endif