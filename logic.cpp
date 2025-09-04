#include "logic.h"
#include <iostream>
using namespace std;

bool inrange(sf::Vector2f pos1, sf::Vector2f pos2, int range){
    return (abs(sqrt(pow(pos1.x,2)-pow(pos2.x,2)+pow(pos1.y,2)-pow(pos2.y,2))))<=range;
}
void attack(vector <tower> towers, vector <enemy> enemies,float current_time,sf::Vector2f center, vector <sf::Vector2f> path){
	for(int i=0;i<towers.size();i++){
		float last_hit=towers[i].get_lastattack(current_time);
		if(last_hit<=0.0f){
			sf::Vector2f tower_pos=towers[i].get_pos();
			int range=towers[i].get_range();
			vector <enemy> enemy_inrange;
            enemy_inrange.clear();
            enemy_inrange.reserve(enemies.size());
			for(auto& enemy:enemies){
				sf::Vector2f enemy_pos=enemy.get_pos();
				if(inrange(tower_pos,enemy_pos,range)){
					enemy_inrange.push_back(enemy);
				}
			}
			sort(enemy_inrange,path,center);
			enemy_inrange[0].damaged(towers[i].get_damage());
		}			
	}
}
void sort(vector <enemy> &enemies, vector <sf::Vector2f> path,sf::Vector2f center){
	for(int i=0;i<path.size()-1;i++){
		if(path[i].x==path[i+1].x){
			std::vector <enemy> enemy_onpath;
			for(int j=0;j<enemies.size();j++){
				if(enemies[j].get_pos().x==path[i].x && (enemies[j].get_pos().y-path[i].y)*(enemies[j].get_pos().y-path[i+1].y)<=0)enemy_onpath.push_back(enemies[j]);
			}
			sort_byy(enemy_onpath,center.x);			
		}
		else{
			vector <enemy> enemy_onpath;
			for(int j=0;j<enemies.size();j++){
				if(enemies[j].get_pos().y==path[i].y && (enemies[j].get_pos().x-path[i].x)*(enemies[j].get_pos().x-path[i+1].x)<=0)enemy_onpath.push_back(enemies[j]);
			}
			sort_byx(enemy_onpath,center.y);	
		}
		
	}	
}
void sort_byy(vector <enemy> &enemies,float half){
	if(enemies[0].get_pos().x>half){
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i].get_pos().y<enemies[j].get_pos().y)swap(enemies[i],enemies[j]);
			}
		}
	}
	else{
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i].get_pos().y>enemies[j].get_pos().y)swap(enemies[i],enemies[j]);
			}
		}
	}
}
void sort_byx(vector <enemy> &enemies,float half){
	if(enemies[0].get_pos().y>half){
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i].get_pos().x>enemies[j].get_pos().x)swap(enemies[i],enemies[j]);
			}
		}
	}
	else{
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i].get_pos().x<enemies[j].get_pos().x)swap(enemies[i],enemies[j]);
			}
		}
	}
}
