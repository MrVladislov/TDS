//g++ main.cpp -o game.exe -I"D:\Vlad\SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.0\include" -L"D:\Vlad\SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.0\lib" -lsfml-graphics -lsfml-window -lsfml-system
#include <vector>
#include <iostream>
#include <string> 
#include "visual.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    string game_name = "TDS";
    GameUI game(552, 352, game_name, 100, 10);
    while (game.isOpen()) {
        if(game.pollEvent()){
            game.close();
        }
        game.render(100, 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            game.close();
        }
        sf::sleep(sf::milliseconds(15));
    }
    return 0;
}