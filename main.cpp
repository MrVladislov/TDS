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
    int balance=100,health=10,speed=0;
    float time=0.f;
    vector <sf::Vector2f> path{{0.0f,96.0f},{608.0f,96.0f},{608.0f,608.0f},{96.0f,608.0f},{96.0f,224.0f},{480.0f,224.0f},{480.0f,480.0f},{224.0f,480.0f},{224.0f,352.0f},{352.0f,352.0f}};
    for(auto & point:path){
        point.x+=10.0f;
        point.y+=10.0f;
    }
    while(choice=='y'){
        balance=200;
        health=10;
        cout<<"Speed:";
        cin>>speed;
        try {
            string game_name = "TDS";
            GameUI game(1280, 720, game_name, balance, health,path);
            while (game.isOpen()) {
                if(game.pollEvent()){
                    game.close();
                }
                time=speed*game.restartClock();
                game.render(balance, health,time);
                if (game.isButtonPressed(sf::Keyboard::Scancode::Escape)) {
                    game.close();
                }
                auto[enemies,towers]=game.get_entities();
                if(enemies.size()>0)attack(towers,enemies,time,path[path.size()-1],path,balance);
                //cout<<game.restartClock()<<endl;
                if(health<=0)break;
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }
        cout<<"Try again? (y/n): ";
        cin>>choice;
    }
    return 0;
}