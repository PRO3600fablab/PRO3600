#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Window.hpp>


#include <iostream>

#ifndef __Widget_h_
#define __Widget_h_
#include "Widget.h"
#endif 

class Button: public Widget {
    public:
    //initialisation
    Button();
    Button(int tsize,sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1, std::string text,bool * render);

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
    int textSize;
    sf::Vector2f size;
    int location[2];
    sf::Text textbox;
    sf::Color color;
    bool isSelected = false;
    sf::RectangleShape contour;

};
