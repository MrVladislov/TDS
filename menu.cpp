#include "menu.h"
menu::menu(int balance,int health,int waves){
    texts.clear();
    arialmt = sf::Font("arialmt.ttf");
    background.setSize(sf::Vector2f(200.0f, 720.0f));
    background.setPosition(sf::Vector2f(1080.0f, 0.0f));
    background.setFillColor(sf::Color(96, 96, 96));
    sf::Text text(arialmt, "Balance:" + std::to_string(balance), 12);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(1100.0f, 10.0f));
    texts.push_back(text);
    sf::Text text2(arialmt, "Health:" + std::to_string(health), 12);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(1100.0f, 30.0f));
    texts.push_back(text2);
    sf::Text text3(arialmt, "Wave:" + std::to_string(waves), 12);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(sf::Vector2f(1100.0f, 50.0f));
    texts.push_back(text3);
    Button button(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 100.0f), "Archer tower ("+std::to_string(getTowerCost(0))+")",
     sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button);
    Button button2(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 140.0f), "Mage tower ("+std::to_string(getTowerCost(1))+")",
     sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button2);
    Button button3(sf::Vector2f(120.0f, 30.0f), sf::Vector2f(1100.0f, 180.0f), "Sniper tower ("+to_string(getTowerCost(2))+")",
     sf::Color(160, 160, 160),arialmt);
    buttons.push_back(button3);
};
void menu::draw(sf::RenderTarget &target){
    target.draw(background);
    for(auto &text : texts){
        target.draw(text);
    }
    for(auto &button : buttons){
        button.draw(target);
    }
};
void menu::changeStats(int balance, int health,int waves){
    this->texts[0].setString("Balance:"+to_string(balance));
    this->texts[1].setString("Health:"+to_string(health));
    this->texts[2].setString("Waves:"+to_string(waves));
};
void menu::TowerBuy(sf::Window &target){
    for(int i=0;i<buttons.size();i++){
    sf::FloatRect rect=buttons[i].get_bound();
    sf::Vector2f mouse_pos=sf::Vector2f(sf::Mouse::getPosition(target));
    //cout<<"mouse "<<mouse_pos.x<<" "<<mouse_pos.y<<endl<<"but "<<rect.position.x<<" "<<rect.position.y<<endl;
        if(rect.contains(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouse_clicked){
            //cout<<"Button "<<i<<" "<<selected_button<<endl;
            mouse_clicked=1;
            if(selected_button!=i){
                selected_button=i;
                buttons[i].selected();
                break;
            }
            else{
                selected_button=-1;
                buttons[i].unselected();
                break;
            }
        }
    }
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))mouse_clicked=0;
    for(int i=0;i<buttons.size();i++){
        if(i!=selected_button || selected_button==-1)
            buttons[i].unselected();
    }
};
int menu::getSelectedTower(){
    return selected_button;
};