#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
#ifndef __Widget_h_
#define __Widget_h_
#include "Widget.h"
#endif 
//size convention : 
/*
the cursor is 10% the size of the bar
so the bar starts and ends 5% before the limit defined by the variable location
*/


class ScrollBar : public Widget {

    void initShapes(int loc0, int loc1);

    //getter & setter
    void changeProgress(float pro);

    //render function
    
    void updateCursor();
    
    void chooseColor(bool b);
    
    void drawTo(sf::RenderWindow &window);

    bool render(bool clicked,sf::RenderWindow &window);

    bool detect(sf::RenderWindow &window);
    //utilitary fonction


    private:
    float progress;//float between 0 and 1, "percentage" of where the cursor is
    sf::Vector2f size;
    int location[2];
    sf::Color colorBar;
    sf::Color colorCursor;
    bool wasSelected = false;
    float oldMouseX=0;
    sf::RectangleShape contourBar;
    sf::RectangleShape contourCursor;

};
