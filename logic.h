#ifndef LOGIC_H
#define LOGIC_H
#include "entity.h"
#include <cmath>
#include "visual.h"
#include <vector>
#include <SFML/System.hpp>

#pragma once
/**
 * @brief Check if pos2 is within a given range from pos1.
 * @param pos1 First position (center point).
 * @param pos2 Second position (position being checked).
 * @param range Maximum allowed distance.
 * @return True if the distance between pos1 and pos2 is less than or equal to range, otherwise false.
 */
bool inrange(sf::Vector2f pos1, sf::Vector2f pos2, int range);
/**
 * @brief Handles tower attacks on enemies.
 * @param towers Vector of towers (modified only last_attack).
 * @param enemies Vector of enemies (modified health).
 * @param current_time Time elapsed since the last frame.
 * @param center Center point of the map (used for sorting logic).
 * @param path Path followed by enemies.
 * @param balance Reference to player's current balance (updated when enemies are died after attack).
 */
void attack(vector <tower> &towers, vector <enemy> &enemies,float current_time,sf::Vector2f center, vector <sf::Vector2f> path,
int &balance);
/**
 * @brief Sort enemies based on their position along the path.
 * @param enemies Vector of enemy pointers to be sorted (modified only order).
 * @param path Path points that enemies follow.
 * @param center Center point of the map (used for determining sort direction).
 */
void sort(vector <enemy*> &enemies, vector <sf::Vector2f> path,sf::Vector2f center);
/**
 * @brief Sort enemies by Y coordinate relative to a reference point.
 * @param enemies Vector of enemy pointers to be sorted.
 * @param half Reference X coordinate to determine sorting order.
 */
void sort_byy(vector <enemy*> &enemies,float half);
/**
 * @brief Sort enemies by X coordinate relative to a reference point.
 * @param enemies Vector of enemy pointers to be sorted (modified only order).
 * @param half Reference Y coordinate to determine sorting order.
 */
void sort_byx(vector <enemy*> &enemies,float half);
#endif