#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

/**
 * @brief UI Button class for the game interface.
 */
class Button{
private:
    sf::RectangleShape shape;///< Button shape.
    sf::Text text;///< Text displayed on the button.
public:
    /**
     * @brief Constructs a button.
     * @param size Size of the button.
     * @param position Position of the button.
     * @param text Text to display on the button.
     * @param color Button color.
     * @param font Font used for text.
     */
    Button(sf::Vector2f size, sf::Vector2f position, std::string text, sf::Color color,sf::Font &font);
    /**
     * @brief Draws the button on the target.
     * @param target Render target (e.g., window).
     */
    void draw(sf::RenderTarget &target);
    /**
     * @brief Gets the bounding rectangle of the button.
     * @return The bounding rectangle as sf::FloatRect.
     */
    sf::FloatRect get_bound() const;
    /**
     * @brief Marks the button as selected.
     */
    void selected();
    /**
     * @brief Marks the button as unselected.
     */
    void unselected();
};

#endif