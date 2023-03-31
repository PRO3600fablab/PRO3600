#include <SFML/Graphics.hpp>
#include <iostream>
//size convention : 
/*
the cursor is 10% the size of the bar
so the bar starts and ends 5% before the limit defined by the variable location
*/


class ScrollBar{
    public:
    //initialisation
    ScrollBar(){}
    ScrollBar(sf::Color color,bool sel,int loc0,int loc1, int siz0, int siz1,float progress){
        //conversion
        sf::Vector2f x(loc0,loc1);
        changeProgress(progress);

        //affectation
        sf::Vector2f v(siz0,siz1);
        size=v;
        location[0]=loc0;
        location[1]=loc1;
        //rectangle
        initShapes(loc0,loc1);
    };

    void initShapes(int loc0, int loc1){
        //initializing the bar
        sf::Vector2f barSize(0.9*size.x,size.y);
        contourBar = sf::RectangleShape(barSize);
        contourBar.setPosition(loc0+0.05*size.x, loc1);
        contourBar.setFillColor(sf::Color(100,100,100));
        contourBar.setOutlineColor(sf::Color::White);
        //initializing the cursor
        //we need to manage the offset
        sf::Vector2f cursorSize(0.1*size.x,size.y);
        contourCursor = sf::RectangleShape(cursorSize);
        contourCursor.setPosition(loc0+0.90*progress*size.x, loc1);
        contourCursor.setFillColor(sf::Color(150,150,150));
        contourCursor.setOutlineColor(sf::Color::White);

    };

    //getter & setter
    void changeProgress(float pro){
        if(pro>1){
            progress=1;
        }
        else if(pro<0){
            progress=0;
        }
        else{
            progress = pro;
        };
    };

    //render function
    
    void updateCursor(){
        contourCursor.setPosition(location[0]+0.90*progress*size.x, location[1]);
    };
    
    void chooseColor(bool b){
        //if selected we choose the brighter color
        if(b){
            contourCursor.setFillColor(sf::Color::White);
        }
        else{
            contourCursor.setFillColor(sf::Color(150,150,150));
        };

    };
    
    void drawTo(sf::RenderWindow &window){
        window.draw(contourBar);
        window.draw(contourCursor);
    };

    void render(bool clicked,sf::RenderWindow &window){
        //if the button is and was clicked earlier we change progress to the corresponding value

        //detection
        bool detected = detect(window);
        bool isSelected;
        if(wasSelected){
            isSelected=clicked;
        }
        else{
            isSelected=clicked && detected;
        }
        float mouseX = sf::Mouse::getPosition(window).x;
        float delta = mouseX-oldMouseX;
        //true if the bar is "held"
        if (isSelected && wasSelected){
            //we need to convert the delta in x into percentage
            float addProgress=delta/size.x/0.9;
            changeProgress(progress+addProgress);
            updateCursor();
        }
        //memorizing old configuration
        oldMouseX=mouseX;
        wasSelected=isSelected;//isheld
        //choosing color and drawing
        chooseColor(isSelected||detected);
        drawTo(window);
    };

    bool detect(sf::RenderWindow &window){
        bool result = true;
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;
        //coordinate of corners
        float minX = location[0]+0.9*progress*size.x;
        float minY = location[1];
        float maxX = minX+0.1*size.x;
        float maxY = minY+size.y;
        //we check if the mouse is inside the frame
        result&=(minX<mouseX);
        result&=(mouseX<maxX);
        result&=(minY<mouseY);
        result&=(mouseY<maxY);
        return result;
    };
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