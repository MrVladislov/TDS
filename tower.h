#ifndef TOWER_H
#define TOWER_H
#include "entity.h"


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
 * @brief Gets the cost of a tower by type index.
 * @param typ Type index.
 * @return Cost value.
 */
int getTowerCost(int typ);



/**
 * @brief Gets the attack speed of a tower type.
 * @param typ Tower type.
 * @return Attack speed.
 */
double getTowerAttackSpeed(tower_type typ);
#endif