#include <SFML/Graphics.hpp>
#include <iostream>
#include "Widget.h"
class ButtonSwitch:public Widget{
    public:
    //initialisation
    ButtonSwitch(){};
    ButtonSwitch(int tsize,sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1, std::string textTrue,std::string textFalse){};

    void initRectangle(int loc0, int loc1){};

    //getter & setter
    void setFont(sf::Font &font){};

    void changePosition(float pos[2]){};

    //render function
    void chooseColor(bool b){};

    void drawTo(sf::RenderWindow &window){};

    bool render(bool clicked,sf::RenderWindow &window){};

    bool detect(sf::RenderWindow &window){};
    
    private:
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