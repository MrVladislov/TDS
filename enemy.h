#ifndef ENEMY_H
#define ENEMY_H
#include "entity.h"
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
 * @brief Converts an enemy type to a string.
 * @param type Enemy type.
 * @return Enemy type as string.
 */
std::string enemyTypeToString(enemy_type type);
/**
 * @brief Returns enemy stats based on its type.
 * @param type Enemy type.
 * @return Tuple of (speed, health).
 */
std::tuple<int,int> enemyTypeToStats(enemy_type type);
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
#endif
