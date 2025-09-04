#ifndef LOGIC_H
#define LOGIC_H
#include "entity.h"
#include <cmath>
#include "visual.h"
#include <vector>
#include <SFML/System.hpp>

#pragma once
bool inrange(sf::Vector2f pos1, sf::Vector2f pos2, int range);
void attack(vector <tower> towers, vector <enemy> enemies,float current_time,sf::Vector2f center, vector <sf::Vector2f> path);
void sort(vector <enemy> &enemies, vector <sf::Vector2f> path,sf::Vector2f center);
void sort_byy(vector <enemy> &enemies,float half);
void sort_byx(vector <enemy> &enemies,float half);

#endif