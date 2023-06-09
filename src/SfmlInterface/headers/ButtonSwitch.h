
#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
#ifndef __Widget_h_
#define __Widget_h_
#include "Widget.h"
#endif 

class ButtonSwitch : public Widget{
    public:
    //initialisation
    ButtonSwitch();
    ButtonSwitch(int tsize,sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1, std::string textTrue,std::string textFalse, bool * render);
	//ButtonSwitch(int tsize,sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1, std::string textTrue,std::string textFalse, bool * render){};

    void initRectangle(int loc0, int loc1);

    //getter & setter
    void setFont(sf::Font &font);

    void changePosition(float pos[2]);

    //render function
    void chooseColor(bool b);

    void drawTo(sf::RenderWindow &window);

    void render(sf::RenderWindow &window, bool clicked) override;

    bool detect(sf::RenderWindow &window);
    
    private:
    bool * renderValue;
    std::string textContent[2];// textContent[0] is text to display when false, 1 when true
    bool state;
    int textSize;
    sf::Vector2f size;
    int location[2];
    sf::Text textbox;
    sf::Color color;
    bool isSelected = false;
    sf::RectangleShape contour;

};
