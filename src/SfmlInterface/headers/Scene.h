#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
#include "ButtonSwitch.h"
#include "Button.h"
#include "InputBox.h"
#ifndef __Widget_h_
#define __Widget_h_
#include "Widget.h"
#endif 

using namespace std ;



class Scene{
    public:
    Scene();

    void addWidget(Widget* wid);

    void render(sf::RenderWindow &window,bool clicked);


    private:
	vector <Widget*> collection;
};
