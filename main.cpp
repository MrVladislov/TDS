#include <vector>
#include <iostream>
#include <string> 
#include "visual.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    try {
        string game_name = "TDS";
        GameUI game(1280, 720, game_name, 100, 10);
        while (game.isOpen()) {
            if(game.pollEvent()){
                game.close();
            }
            game.render(100, 10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                game.close();
            }
            sf::sleep(sf::milliseconds(15));
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}