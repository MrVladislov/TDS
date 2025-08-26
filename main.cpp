#include <functional>
#include <vector>
#include <iostream>
#include <string> 
#include "visual.h"


int main() {
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(1000, 600)),
        "TD Game",
        sf::Style::Titlebar | sf::Style::Close
    );

    sf::Font font;
    if (!font.openFromFile("arialmt.ttf")) { // Убедитесь, что файл шрифта доступен
        std::cerr << "Failed to load font!\n";
        return 1;
    }

    GameUI ui(window, font);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            ui.handleEvent(*event);
        }

        ui.update(150, 10);
        window.clear(sf::Color(30, 30, 30));
        ui.draw();
        window.display();
    }

    return 0;
}