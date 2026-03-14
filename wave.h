#ifndef WAVE_H
#define WAVE_H
#include "enemy.h"

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
 * @brief Calculates a sigmoid-based value (used for scaling).
 * @param x Input value.
 * @return Sigmoid result.
 */
float sigmoidF(int x);

#endif