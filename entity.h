#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
//#include "visual.h"
using namespace std;
#pragma once

class entity{
protected:
	sf::Sprite shape;
	sf::Vector2f position;
public:
    entity(sf::Texture &textur);
	void draw(sf::RenderTarget &target);
    sf::Vector2f get_pos() const;
};
enum enemy_type{
red_slime,
blue_slime,
king_slime
};
class enemy:public entity{
private:
	int speed;
	int health;
    double buff;
	enemy_type type;
    sf::RectangleShape health_bar;
public:
	enemy(enemy_type typ,sf::Texture &textur);
	void move(float delta_time,vector <sf::Vector2f> path);
	bool damaged(int damage);
    void set_pos(sf::Vector2f spawn_point);
    bool draw(sf::RenderTarget &target);
    enemy_type get_type() const;
    void Buff(double buff);
};
enum tower_type{
archer,
mage,
sniper
};

class tower:public entity{
private:
	int damage;
	int damage_area;
	tower_type type;
	int attack_type;
	float last_attack;
	double attack_speed;
	int range;
    int cost;
public:
	tower(tower_type typ,sf::Texture &textur,sf::Vector2f position);
	float get_lastattack(float deltaT);
	int get_damage() const;
	int get_range() const; 
	double get_attackspeed() const;
    int getCost() const;
    void set_lastattack(float next_attack);
    tower_type get_type() const;
    int get_damagearea() const;
};
class wave{
    private:
        vector <enemy> enemies;
        vector <enemy> new_enemies;
        int wave_number;
        vector <sf::Vector2f> path;
        vector <sf::Texture> enemy_textures;
        float last_spawn_time;
        std::vector <sf::Vector2f> e_path;
    public:
        wave(std::vector <sf::Vector2f> path,int wave=0);
        void next_wave();
        vector <enemy>& get_enemies();
        bool spawn_enemies(float current_time);
        int getWave() const;
        float getWaveLong() const;
        void draw(sf::RenderTarget &target,float deltaT);
};

std::string enemyTypeToString(enemy_type type);
std::string towerTypeToString(tower_type type);
std::tuple<int,double,int,int,int> towerTypeToStats(tower_type type);
std::tuple<int,int> enemyTypeToStats(enemy_type type);
int getTowerCost(int typ);
float sigmoidF(int x);
int getEnemyCost(int typ);
int getEnemyHealth(enemy_type typ);
#endif