#include <vector>
#include <iostream>
#include <string> 
#include "visual.h"
#include "entity.h"
#include "logic.h"
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    char choice='y';
    vector <sf::Vector2f> path{{0.0f,96.0f},{608.0f,96.0f},{608.0f,608.0f},{96.0f,608.0f},{96.0f,224.0f},{96.0f,480.0f},{480.0f,480.0f},{352.0f,480.0f},{224.0f,352.0f},{352.0f,352.0f}};
    for(auto & point:path){
        point.x+=10.0f;
        point.y+=10.0f;
    }
    while(choice=='y'){
        try {
            string game_name = "TDS";
            GameUI game(1280, 720, game_name, 100, 10);
            while (game.isOpen()) {
                if(game.pollEvent()){
                    game.close();
                }
                game.render(100, 10);
                if (game.isButtonPressed(sf::Keyboard::Scancode::Escape)) {
                    game.close();
                }
                //cout<<game.restartClock()<<endl;
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }
        cout<<"Try again? (y/n): ";
        cin>>choice;
    }
    return 0;
}