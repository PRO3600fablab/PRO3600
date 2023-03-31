#include <SFML/Graphics.hpp>
#include <iostream>
#include "Widget.h"
class Button : public Widget {
    public:
    //initialisation
    Button(){}
    Button(int tsize,sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1, std::string text){
        
    };

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
    int textSize;
    sf::Vector2f size;
    int location[2];
    sf::Text textbox;
    sf::Color color;
    bool isSelected = false;
    sf::RectangleShape contour;

};