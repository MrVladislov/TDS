#include "button.h"
#include <SFML/Graphics.hpp>
Button::Button(sf::Vector2f size, sf::Vector2f position, std::string text, sf::Color color, sf::Font &font) 
:text(font, text, 12)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color(255,0,0));
    shape.setOutlineThickness(0.0f);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(position + sf::Vector2f(1.0f, 5.0f));
};
void Button::draw(sf::RenderTarget &target) {
    target.draw(shape);
    target.draw(text);
};
sf::FloatRect Button::get_bound() const { return shape.getGlobalBounds(); }
void Button::selected(){
    shape.setOutlineThickness(2.0f);
}
void Button::unselected(){
    shape.setOutlineThickness(0.0f);
}