#ifndef MENU_H
#define MENU_H
#include "button.h"
#include "tower.h"
/**
 * @brief UI menu for displaying game stats and buttons.
 */
class menu{
private:
    std::vector<Button> buttons;///< Buttons in the menu.
    std::vector<sf::Text> texts;///< Text elements in the menu.
    sf::RectangleShape background;///< Background of the menu.
    sf::Font arialmt;///< Font used for text.
    int selected_button=-1;///< Index of the selected button.
    bool mouse_clicked=false;///< Mouse click state.
public:
    /**
     * @brief Constructs the menu with initial stats.
     * @param balance Player's balance.
     * @param health Player's health.
     * @param waves Current wave number.
     */
    menu(int balance,int health,int waves=0);
    /**
     * @brief Draws the menu on the target.
     * @param target Render target.
     */
    void draw(sf::RenderTarget &target);
    /**
     * @brief Updates displayed stats.
     * @param balance Player's balance.
     * @param health Player's health.
     * @param waves Current wave number.
     */
    void changeStats(int balance,int health,int waves);
    /**
     * @brief Handles tower purchase UI logic.
     * @param target Game window.
     */
    void TowerBuy(sf::Window &target);
    /**
     * @brief Gets the selected tower type.
     * @return Tower type index.
     */
    int getSelectedTower();
};

#endif