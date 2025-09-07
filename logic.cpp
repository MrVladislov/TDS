#include "logic.h"
#include <iostream>
using namespace std;

bool inrange(sf::Vector2f pos1, sf::Vector2f pos2, int range){
    return ((sqrt(pow(pos1.x-pos2.x,2)+pow(pos1.y-pos2.y,2)))<=range);
}
void attack(vector <tower> &towers, vector <enemy> &enemies,float current_time,sf::Vector2f center, vector <sf::Vector2f> path,
int &balance){
	for(int i=0;i<towers.size();i++){
		float last_hit=towers[i].get_lastattack(current_time);
		if(last_hit<=0.0f){
            towers[i].set_lastattack(towers[i].get_attackspeed());
			sf::Vector2f tower_pos=towers[i].get_pos();
			int range=towers[i].get_range();
			vector <enemy*> enemy_inrange;
            enemy_inrange.clear();
            enemy_inrange.reserve(enemies.size());
			for(auto& enemy:enemies){
				sf::Vector2f enemy_pos=enemy.get_pos();
				if(inrange(tower_pos,enemy_pos,range)){
					enemy_inrange.push_back(&enemy);
				}
			}
			if(enemy_inrange.size()>0)
            {
                towers[i].set_lastattack();
                sort(enemy_inrange,path,center);
                int damage_area=towers[i].get_damagearea();
                vector <enemy*> enemies_in_area;
                int choosen=-1;
                if(towers[i].get_type()==tower_type::sniper){
                    for(int i=0;i<enemy_inrange.size();i++){
                        if(enemy_inrange[i]->get_type()==enemy_type::king_slime){
                            choosen=i;
                            break;
                        }
                    }
                    if(choosen==-1){
                        for(int i=0;i<enemy_inrange.size();i++){
                            if(enemy_inrange[i]->get_type()==enemy_type::red_slime){
                                choosen=i;
                                break;
                            }
                        }
                    }
                    if(choosen==-1)choosen=0;
                }
                else choosen=0;
                for(auto &enemy:enemies){
                    if(inrange(enemy.get_pos(),enemy_inrange[choosen]->get_pos(),damage_area)){
                        enemies_in_area.push_back(&enemy);
                    }
                }
                for(auto &enemy:enemies_in_area){
                    if(enemy->damaged(towers[i].get_damage()))balance+=getEnemyCost(enemy->get_type());
                }
            }
		}			
	}
}
void sort(vector <enemy*> &enemies, vector <sf::Vector2f> path,sf::Vector2f center){
	for(int i=0;i<path.size()-1;i++){
		if(path[i].x==path[i+1].x){
			std::vector <enemy*> enemy_onpath;
			for(int j=0;j<enemies.size();j++){
				if(enemies[j]->get_pos().x==path[i].x && (enemies[j]->get_pos().y-path[i].y)*(enemies[j]->get_pos().y-path[i+1].y)<=0)enemy_onpath.push_back(enemies[j]);
			}
			if(enemy_onpath.size()>0)sort_byy(enemy_onpath,center.x);			
		}
		else{
			vector <enemy*> enemy_onpath;
			for(int j=0;j<enemies.size();j++){
				if(enemies[j]->get_pos().y==path[i].y && (enemies[j]->get_pos().x-path[i].x)*(enemies[j]->get_pos().x-path[i+1].x)<=0)enemy_onpath.push_back(enemies[j]);
			}
            if(enemy_onpath.size()>0)sort_byx(enemy_onpath,center.y);	
		}
		
	}	
}
void sort_byy(vector <enemy*> &enemies,float half){
	if(enemies[0]->get_pos().x>half){
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i]->get_pos().y<enemies[j]->get_pos().y)swap(enemies[i],enemies[j]);
			}
		}
	}
	else{
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i]->get_pos().y>enemies[j]->get_pos().y)swap(enemies[i],enemies[j]);
			}
		}
	}
}
void sort_byx(vector <enemy*> &enemies,float half){
	if(enemies[0]->get_pos().y>half){
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i]->get_pos().x>enemies[j]->get_pos().x)swap(enemies[i],enemies[j]);
			}
		}
	}
	else{
		for(int i=0;i<enemies.size()-1;i++){
			for(int j=i+1;j<enemies.size();j++){
				if(enemies[i]->get_pos().x<enemies[j]->get_pos().x)swap(enemies[i],enemies[j]);
			}
		}
	}
}
