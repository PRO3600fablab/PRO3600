#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef __Widget_h_
#define __Widget_h_
#include "Widget.h"
#endif 
#define proportion 0.6
class InputBox : public Widget{
    public:
    //initialisation
    InputBox();
    InputBox(sf::Color colorarg,int loc0,int loc1, int siz0, int siz1,sf::Font &font, float * render);

    void initRectangles(int loc0, int loc1);
    
    void initTexts(sf::Font &font);

    //getter & setter
    void setFont(sf::Font &font);

    //render function
    void chooseColor(int i);
    
    void drawTo(sf::RenderWindow &window);

    void render(bool clicked,sf::RenderWindow &window);

    int detect(sf::RenderWindow &window);
    
    private:
    float * renderValue;
    //geometric properties
    sf::Vector2f size;
    sf::Vector2f location;
    //texts
    int textSize;
    sf::Text unityText;
    sf::Text valueText;
    int isSelected = 0;
    bool isReading=false;// is true when the text area is clicked so the button read the input to change the value
    //value contained in the widget
    float value=0;
    float borneValue[2];
    //shapes and color
    sf::Color color;
    sf::RectangleShape contourText;//text input
    sf::RectangleShape boxIncr;//background for increase
    sf::RectangleShape boxDecr;//background for decrease 
    sf::RectangleShape arrowIncr;//arrow to increase by one the value
    sf::RectangleShape arroxDecr;//arrow to decrease by one the value
};