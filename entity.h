#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;



class entity{
protected:
	sf::Sprite shape;
	sf::Vector2f position;
	sf::Texture texture;
public:
    entity() =default;
    entity(sf::Texture &textur);
	void draw(sf::RenderTarget &target);
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
	enemy_type type;
public:
	enemy(enemy_type typ,sf::Texture textur);
	void move(double delta_time,vector <sf::Vector2f> path);
	sf::Vector2f get_pos();
	bool damaged(int damage);
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
    sf::Texture texture;
public:
	tower(tower_type typ,sf::Texture textur,sf::Vector2f position);
	float get_lastattack(float deltaT);
	int get_damage() const;
	sf::Vector2f get_pos() const;
	int get_range() const; 
	double get_attackspeed() const;
};
class wave{
    private:
        vector <enemy> enemies;
        vector <enemy> new_enemies;
        int wave_number;
        vector <sf::Vector2f> path;
        vector <sf::Texture> enemy_textures;
        float last_spawn_time;
    public:
        wave(int wave=1);
        void next_wave();
        vector <enemy> get_enemies() const;
        bool spawn_enemies(float current_time);
};
#pragma once
std::string enemyTypeToString(enemy_type type);
std::string towerTypeToString(tower_type type);
#endif