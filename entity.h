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
/**
 * @brief Types of enemies in the game.
 */
enum enemy_type{
red_slime,
blue_slime,
king_slime
};
/**
 * @brief Represents an enemy in the game.
 */
class enemy:public entity{
private:
	int speed;///< Movement speed of the enemy.
	int health;///< Current health of the enemy.
    double buff;///< Buff modifier applied to the enemy.
	enemy_type type;///< Type of the enemy.
    sf::RectangleShape health_bar;///< Health bar of the enemy.
public:
    /**
     * @brief Constructs an enemy of a specific type with a given texture.
     * @param typ Enemy type.
     * @param textur Texture for the enemy sprite.
     */
	enemy(enemy_type typ,sf::Texture &textur);
    /**
     * @brief Moves the enemy along the given path.
     * @param delta_time Time elapsed since last frame.
     * @param path Path points for the enemy to follow.
     */
	void move(float delta_time,vector <sf::Vector2f> path);
    /**
     * @brief Reduces enemy health by the given damage amount.
     * @param damage Damage to apply.
     * @return True if enemy is dead (health <= 0), false otherwise.
     */
	bool damaged(int damage);
    /**
     * @brief Sets enemy position to the given point (used for spawning).
     * @param spawn_point Position where the enemy should be placed.
     */
    void set_pos(sf::Vector2f spawn_point);
    /**
     * @brief Draws the enemy and its health bar.
     * @param target Render target (e.g., window).
     * @return True if successfully drawn.
     */
    bool draw(sf::RenderTarget &target);
    /**
     * @brief Gets the enemy type.
     * @return Enemy type.
     */
    enemy_type get_type() const;
    /**
     * @brief Applies a buff to the enemy.
     * @param buff Buff multiplier (e.g., 1.2 = +20%).
     */
    void Buff(double buff);
};
/**
 * @brief Types of towers in the game.
 */
enum tower_type{
archer,
mage,
sniper
};
/**
 * @brief Represents a tower in the game.
 */
class tower:public entity{
private:
	int damage;///< Damage dealt by the tower.
	int damage_area;///< Area of effect (for splash damage).
	tower_type type;///< Type of the tower.
	int attack_type;///< Attack type (unused or for future logic).
	float last_attack;///< Time remaining until next attack.
	double attack_speed;///< Speed of attacks (lower is faster).
	int range;///< Attack range.
    int cost;///< Cost to build the tower.
public:
    /**
     * @brief Constructs a tower.
     * @param typ Type of tower.
     * @param textur Texture of the tower.
     * @param position Position to place the tower.
     */
	tower(tower_type typ,sf::Texture &textur,sf::Vector2f position);
    /**
     * @brief Updates and returns time until the next attack.
     * @param deltaT Time elapsed since last frame.
     * @return Updated attack cooldown time.
     */
	float get_lastattack(float deltaT);
    /**
     * @brief Gets the damage dealt by the tower.
     * @return Damage value.
     */
	int get_damage() const;
    /**
     * @brief Gets the attack range of the tower.
     * @return Range value.
     */
	int get_range() const; 
    /**
     * @brief Gets the attack speed of the tower.
     * @return Attack speed (time between shots).
     */
	double get_attackspeed() const;
    /**
     * @brief Gets the cost of the tower.
     * @return Cost value.
     */
    int getCost() const;
    /**
     * @brief Sets the cooldown for the next attack.
     * @param next_attack Time until next attack.
     */
    void set_lastattack(float next_attack);
    /**
     * @brief Gets the tower type.
     * @return Tower type.
     */
    tower_type get_type() const;
    /**
     * @brief Gets the area of effect for attacks.
     * @return Area size.
     */
    int get_damagearea() const;
};
/**
 * @brief Represents a wave of enemies.
 */
class wave{
private:
    vector <enemy> enemies;///< Current active enemies.
    vector <enemy> new_enemies;///< Enemies waiting to spawn.
    int wave_number;///< Current wave number.
    vector <sf::Vector2f> path;///< Path for enemies to follow.
    vector <sf::Texture> enemy_textures;///< Textures for enemy types.
    float last_spawn_time;///< Time since last enemy spawned.
    std::vector <sf::Vector2f> e_path;///< Extra path storage.
public:
    /**
     * @brief Constructs a wave with a given path.
     * @param path Enemy path.
     * @param wave Initial wave number (default 0).
     */
    wave(std::vector <sf::Vector2f> path,int wave=0);
    /**
     * @brief Prepares the next wave of enemies.
     */
    void next_wave();
    /**
     * @brief Returns a reference to the current enemies.
     * @return Reference to vector of enemies.
     */
    vector <enemy>& get_enemies();
    /**
     * @brief Spawns enemies based on time and wave logic.
     * @param current_time Current time in seconds.
     * @return True if wave is complete (all enemies spawned), false otherwise.
     */
    bool spawn_enemies(float current_time);
    /**
     * @brief Gets the current wave number.
     * @return Wave number.
     */
    int getWave() const;
    /**
     * @brief Gets the estimated duration of the wave.
     * @return Duration in seconds.
     */
    float getWaveLong() const;
    /**
     * @brief Draws all enemies in the wave.
     * @param target Render target (e.g., window).
     * @param deltaT Time elapsed since last frame.
     */
    void draw(sf::RenderTarget &target,float deltaT);
};

/**
 * @brief Converts an enemy type to a string.
 * @param type Enemy type.
 * @return Enemy type as string.
 */
std::string enemyTypeToString(enemy_type type);
/**
 * @brief Converts a tower type to a string.
 * @param type Tower type.
 * @return Tower type as string.
 */
std::string towerTypeToString(tower_type type);
/**
 * @brief Returns tower stats based on its type.
 * @param type Tower type.
 * @return Tuple of (damage, attack_speed, range, damage_area, cost).
 */
std::tuple<int,double,int,int,int> towerTypeToStats(tower_type type);
/**
 * @brief Returns enemy stats based on its type.
 * @param type Enemy type.
 * @return Tuple of (speed, health).
 */
std::tuple<int,int> enemyTypeToStats(enemy_type type);
/**
 * @brief Gets the cost of a tower by type index.
 * @param typ Type index.
 * @return Cost value.
 */
int getTowerCost(int typ);
/**
 * @brief Calculates a sigmoid-based value (used for scaling).
 * @param x Input value.
 * @return Sigmoid result.
 */
float sigmoidF(int x);
/**
 * @brief Gets the reward for killing an enemy.
 * @param typ Enemy type index.
 * @return Reward amount.
 */
int getEnemyCost(int typ);
/**
 * @brief Gets the health of an enemy based on its type.
 * @param typ Enemy type.
 * @return Enemy health.
 */
int getEnemyHealth(enemy_type typ);
/**
 * @brief Gets the attack speed of a tower type.
 * @param typ Tower type.
 * @return Attack speed.
 */
double getTowerAttackSpeed(tower_type typ);
#endif